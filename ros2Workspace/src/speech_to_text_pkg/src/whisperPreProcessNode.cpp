#include "whisperPreProcess.hpp"
#include "pch.hpp"

using namespace std::chrono_literals;

transcriptionPreProcessNode::transcriptionPreProcessNode()
: Node("transcription_pre_process_node"), buffer_(BUFFER_CAPACITY) {

    rclcpp::QoS audio_qos(rclcpp::KeepLast(10));
    audio_qos.best_effort();

    audioPublisher_ = create_publisher<speech_to_text_interfaces::msg::AudioStamped>("/whisper_audio", audio_qos);
    rawAudioSubscriber_ = create_subscription<speech_to_text_interfaces::msg::AudioStamped>(
        "/raw_audio", rclcpp::QoS(10).best_effort(), 
        std::bind(&transcriptionPreProcessNode::audioCallback, this, std::placeholders::_1));
    wakeWordBoolSubscription_ = create_subscription<std_msgs::msg::Bool>(
        "/wakeState", 10, 
        std::bind(&transcriptionPreProcessNode::boolCallback, this, std::placeholders::_1));
    
        samples_.reserve(CHUNK_SIZE * 2);
}

transcriptionPreProcessNode::~transcriptionPreProcessNode() {
    RCLCPP_INFO(get_logger(), "transcription pre processing stopped");
}

void transcriptionPreProcessNode::publishAudio(size_t numSamples) {
    numSamples = std::min(numSamples, samples_.size());
    if(samples_.size() == 0) {
        return;
    }
    
    
    //Drain one 15second chunk
    auto msg = std::make_unique<speech_to_text_interfaces::msg::AudioStamped>();
    msg->sample_rate = SAMPLE_RATE;
    msg->channels = NUM_CHANNELS;
    msg->data.assign(samples_.begin(), samples_.begin() + numSamples);    

    audioPublisher_->publish(std::move(msg));

    RCLCPP_INFO(get_logger(), "Chunk sent");
    

}

void transcriptionPreProcessNode::audioCallback(const speech_to_text_interfaces::msg::AudioStamped::SharedPtr msg) {
    /*
    constantly send /raw_audio samples to pre roll ring buffer
    */
    std::lock_guard<std::mutex> lock(state_mutex_);

    buffer_.push(msg->data.data(), msg->data.size());
    
    auto now = std::chrono::steady_clock::now(); // Static start time
    
    // In audioCallback:
    // In audioCallback:
    if(!vad_.detectSpeech(msg->data.data(), msg->data.size())) {
        if(currentWakeState_ == false) {
            return;
        }

        if(!isSilent_) {
            isSilent_ = true;
            silenceStartTime_ = now;
            return;
        }

        // Accumulate since last check
        totalSilenceDuration_ += std::chrono::duration_cast<std::chrono::milliseconds>(
            now - silenceStartTime_);
        silenceStartTime_ = now; // slide forward, not reset
        
        RCLCPP_INFO(get_logger(), "totalSilenceDuration_ %ld ms", 
        std::chrono::duration_cast<std::chrono::milliseconds>(totalSilenceDuration_).count());

        if(totalSilenceDuration_ >= std::chrono::seconds(15)) {
            currentWakeState_ = false;
            isSilent_ = false;
            totalSilenceDuration_ = std::chrono::milliseconds(0);
            if(!samples_.empty()) {
                publishAudio(samples_.size());
                samples_.clear();
            }
            return;
        }

        if(totalSilenceDuration_ >= std::chrono::milliseconds(1500)) {
            if(samples_.size() >= MIN_CHUNK_SIZE) {
                publishAudio(samples_.size());
                samples_.clear();
            }
            // don't reset totalSilenceDuration_ — keep counting toward 15s
        }

    } else {
        if(isSilent_) {
            // Was silent, now speaking — reset accumulated silence
            isSilent_ = false;
            totalSilenceDuration_ = std::chrono::milliseconds(0);
        }
    }

    if (currentWakeState_) {
        samples_.insert(samples_.end(), msg->data.begin(), msg->data.end());      
    } else {
        //do nothing
        RCLCPP_INFO(get_logger(), "SPEECH");
        return;
    }

    if(isSilent_ && (now - silenceStartTime_ >= std::chrono::milliseconds(1500))) {
        if(samples_.size() >= MIN_CHUNK_SIZE) {
            publishAudio(samples_.size());
            samples_.clear();
        }
        isSilent_ = false;
    } else if (samples_.size() >= CHUNK_SIZE) {
        publishAudio(CHUNK_SIZE);
        samples_.erase(samples_.begin(), samples_.begin() + CHUNK_SIZE);
    }



}

void transcriptionPreProcessNode::boolCallback(const std_msgs::msg::Bool::SharedPtr msg) {
    std::lock_guard<std::mutex> lock(state_mutex_);
    if(msg->data && !currentWakeState_) {
        currentWakeState_ = true;
        auto preRoll = buffer_.peekLast(PRE_ROLL_SIZE);
        samples_.insert(samples_.end(), preRoll.begin(), preRoll.end());
    }
}


int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    try {
        rclcpp::spin(std::make_shared<transcriptionPreProcessNode>());
    } catch (const std::exception& e) {
        RCLCPP_FATAL(rclcpp::get_logger("main"), "Fatal: %s", e.what());
        rclcpp::shutdown();
        return 1;
    }

    rclcpp::shutdown();
    return 0;
    
}



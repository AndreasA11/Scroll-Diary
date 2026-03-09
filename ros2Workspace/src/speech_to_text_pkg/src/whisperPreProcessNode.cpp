#include "whisperPreProcess.hpp"
#include "pch.hpp"

using namespace std::chrono_literals;

transcriptionPreProcessNode::transcriptionPreProcessNode()
: Node("transcription_pre_process_node"), buffer_(BUFFER_CAPACITY) {

    rclcpp::QoS audio_qos(rclcpp::KeepLast(10));
    audio_qos.best_effort();

    publisher_ = create_publisher<speech_to_text_interfaces::msg::AudioStamped>("/whisper_audio", audio_qos);
    raw_audio_subscriber_ = create_subscription<speech_to_text_interfaces::msg::AudioStamped>(
        "/raw_audio", rclcpp::QoS(10).best_effort(), 
        std::bind(&transcriptionPreProcessNode::audioCallback, this, std::placeholders::_1));
    wake_word_bool_subscription_ = create_subscription<std_msgs::msg::Bool>(
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

    publisher_->publish(std::move(msg));

    

}

void transcriptionPreProcessNode::audioCallback(const speech_to_text_interfaces::msg::AudioStamped::SharedPtr msg) {
    /*
    constantly send /raw_audio samples to pre roll ring buffer
    */
    std::lock_guard<std::mutex> lock(state_mutex_);

    buffer_.push(msg->data.data(), msg->data.size());
    
    auto now = std::chrono::steady_clock::now(); // Static start time
    
    if(!vad_.detectSpeech(msg->data.data(), msg->data.size())) {
        if(isQuiet_) {
            //do not adjust the start time
            
            if(now - quietStartTime_ >= std::chrono::seconds(15)) {
                //if we are quiet for more than 15 seconds wakeWordState should default to false
                currentWakeState = false;
                isQuiet_ = false;
                if(!samples_.empty()) {
                    publishAudio(samples_.size());
                }
                samples_.clear();
                return;
            }
        } else {
            //start running the clock for quietTime
            isQuiet_ = true;
            quietStartTime_ = now;
        }
    } else {
        isQuiet_ = false;
    }

    if (currentWakeState) {
        samples_.insert(samples_.end(), msg->data.begin(), msg->data.end());      
    } else {
        //do nothing
        return;
    }

    if(isQuiet_ && (now - quietStartTime_ >= std::chrono::milliseconds(1500))) {
        publishAudio(samples_.size());
        samples_.clear();
        isQuiet_ = false;
    } else if (samples_.size() >= CHUNK_SIZE) {
        publishAudio(CHUNK_SIZE);
        samples_.erase(samples_.begin(), samples_.begin() + CHUNK_SIZE);
    }



}

void transcriptionPreProcessNode::boolCallback(const std_msgs::msg::Bool::SharedPtr msg) {
    std::lock_guard<std::mutex> lock(state_mutex_);
    if(msg->data && !currentWakeState) {
        currentWakeState = true;
        auto preRoll = buffer_.peekLast(PRE_ROLL_SIZE);
        samples_.insert(samples_.end(), preRoll.begin(), preRoll.end());
    }
}


int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    //Devuce ubdex can be overrideen via ROS2 param or argv[1]
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



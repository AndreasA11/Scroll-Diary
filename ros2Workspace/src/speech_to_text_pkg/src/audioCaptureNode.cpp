#include "audioCapture.hpp"


using namespace std::chrono_literals;

//CTOR

AudioCaptureNode::AudioCaptureNode()
: Node("audio_capture_node") {
    rclcpp::QoS audio_qos(rclcpp::KeepLast(10));
    audio_qos.best_effort();

    audioPublisher_ = create_publisher<speech_to_text_interfaces::msg::AudioStamped>("/raw_audio", audio_qos);
    

    ma_uint32 deviceIndex  = listDevices();
    RCLCPP_INFO(get_logger(), "device index we found is %u", deviceIndex);

    if(!initContext()) {
        RCLCPP_FATAL(get_logger(), "Cannot init audio context, shutting down");
        throw std::runtime_error("miniaudio context init failed");
    }

    if (!startLiveCapture(deviceIndex)) {
        RCLCPP_FATAL(get_logger(), "Cannot start capture device, shutting down");
        throw std::runtime_error("miniaudio device start failed");
    }

    //20ms publish timer
    publishTimer_ = create_wall_timer(
        std::chrono::milliseconds(PUBLISH_INTERVAL_MS),
        std::bind(&AudioCaptureNode::publishAudio, this)
    );

    RCLCPP_INFO(get_logger(), 
        "AudioCaptureNode ready, publishing /raw_audio every %u ms "
        "(%u samples/chunk at %u Hz)",
        PUBLISH_INTERVAL_MS, SAMPLES_PER_CHUNK, SAMPLE_RATE        
    );

}

//DTOR

AudioCaptureNode::~AudioCaptureNode() {
    publishTimer_->cancel();
    stopLiveCapture();
    RCLCPP_INFO(get_logger(), "AudioCaptureNode stopped");
}




int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    try {
        rclcpp::spin(std::make_shared<AudioCaptureNode>());
    } catch (const std::exception& e) {
        RCLCPP_FATAL(rclcpp::get_logger("main"), "Fatal: %s", e.what());
        rclcpp::shutdown();
        return 1;
    }

    rclcpp::shutdown();
    return 0;
    
}
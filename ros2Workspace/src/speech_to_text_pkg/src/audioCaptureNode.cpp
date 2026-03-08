#include "audioCapture.hpp"


using namespace std::chrono_literals;

//CTOR

AudioCaptureNode::AudioCaptureNode(ma_uint32 deviceIndex)
: Node("audio_capture_node") {
    rclcpp::QoS audio_qos(rclcpp::KeepLast(10));
    audio_qos.best_effort();

    publisher_ = create_publisher<speech_to_text_interfaces::msg::AudioStamped>("/raw_audio", audio_qos);
    

    listDevices();

    if(!initContext()) {
        RCLCPP_FATAL(get_logger(), "Cannot init audio context, shutting down");
        throw std::runtime_error("miniaudio context init failed");
    }

    if (!startLiveCapture(deviceIndex)) {
        RCLCPP_FATAL(get_logger(), "Cannot start capture device, shutting down");
        throw std::runtime_error("miniaudio device start failed");
    }

    //20ms publish timer
    publish_timer_ = create_wall_timer(
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
    publish_timer_->cancel();
    stopLiveCapture();
    RCLCPP_INFO(get_logger(), "AudioCaptureNode stopped");
}




int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    //Devuce ubdex can be overrideen via ROS2 param or argv[1]
    ma_uint32 deviceIndex = 0;
    if(argc > 1) {
        try {
            deviceIndex = static_cast<ma_uint32>(std::stoul(argv[1]));
        } catch (...) {
            std::cerr << "Usage: audio_capture_node [device_index]\n";
            return 1;
        }
    }

    try {
        rclcpp::spin(std::make_shared<AudioCaptureNode>(deviceIndex));
    } catch (const std::exception& e) {
        RCLCPP_FATAL(rclcpp::get_logger("main"), "Fatal: %s", e.what());
        rclcpp::shutdown();
        return 1;
    }

    rclcpp::shutdown();
    return 0;
    
}
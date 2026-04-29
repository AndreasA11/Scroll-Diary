#pragma once

#include "rclcpp/rclcpp.hpp"
#include "speech_to_text_interfaces/msg/audio_stamped.hpp"
#include "circularBuffer.hpp"
#include "std_msgs/msg/bool.hpp"
#include "rmw/qos_profiles.h"
#include "mutex"
#include "vad.hpp"


static constexpr size_t CHUNK_SIZE = 240000; // ~15 seconds at 16kHz
static constexpr size_t MIN_CHUNK_SIZE = 16000 * 5; // ~5 second minimum
static constexpr size_t BUFFER_CAPACITY = 4 * 240000; // //1 minute of audio time in buffer
static constexpr size_t PRE_ROLL_SIZE = 16000;
static constexpr uint32_t SAMPLE_RATE = 16000;
static constexpr uint32_t NUM_CHANNELS = 1;
 
class transcriptionPreProcessNode : public rclcpp::Node {
    
    private:
        //callback and publishing functions
        void publishAudio(size_t numSamples);
        void audioCallback(const speech_to_text_interfaces::msg::AudioStamped::SharedPtr msg);
        void boolCallback(const std_msgs::msg::Bool::SharedPtr msg);

        bool currentWakeState_ = false;
        CircularBuffer<float> buffer_;
        std::vector<float> samples_;
        LightweightVAD vad_;

        bool isSilent_ = false;
        std::chrono::steady_clock::time_point silenceStartTime_;
        std::chrono::milliseconds totalSilenceDuration_{0};

        mutable std::mutex state_mutex_;
        
        //ROS2 publishers and subscriptions
        rclcpp::Publisher<speech_to_text_interfaces::msg::AudioStamped>::SharedPtr audioPublisher_;
        rclcpp::Subscription<speech_to_text_interfaces::msg::AudioStamped>::SharedPtr rawAudioSubscriber_;
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr wakeWordBoolSubscription_;

    public:
        explicit transcriptionPreProcessNode();
        ~transcriptionPreProcessNode() override;


};

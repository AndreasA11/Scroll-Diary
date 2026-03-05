#pragma once

#include <vector>
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "circularBuffer.hpp"
#include "miniaudio.h"
#include "speech_to_text_interfaces/msg/audio_stamped.hpp"




static constexpr uint32_t SAMPLE_RATE = 16000;
static constexpr uint32_t NUM_CHANNELS = 1;
static constexpr uint32_t PUBLISH_INTERVAL_MS = 20;

//20 ms at 16kHz => 320 samples per chunk
static constexpr uint32_t SAMPLES_PER_CHUNK = (SAMPLE_RATE * PUBLISH_INTERVAL_MS) / 1000;

//1 min of audio room in the buffer
static constexpr size_t BUFFER_CAPACITY = 4 * 240000;



struct LiveCapture {
    ma_context context; 
    ma_device device;
    CircularBuffer<float> buffer; //circular buffer where audio samples are pushed into
    LiveCapture(size_t bufCapacity = BUFFER_CAPACITY) 
        : buffer(bufCapacity) {}  
    
    //no copying
    LiveCapture(const LiveCapture&) = delete;
    LiveCapture& operator=(const  LiveCapture&) = delete;
};

class AudioCaptureNode : public rclcpp::Node {
    public:
        explicit AudioCaptureNode(ma_uint32 deviceIndex = 0);
        ~AudioCaptureNode() override;
    private:
        //Timer callback: drains SAMPLES_PER_CHUNK frames and publishes
        void publishAudio();

        //miniaudio helpers


        //Live capture functions
        /*
        Enumerates and prints all available audio capture devices on the system
        Used to see which device to connect to in startLiveCapture
        */

        void listDevices();

        /* 
        
        */


        bool initContext();

        /*
        configuring ma_device, ma_format_f32, mono channel, 
        16000 sample rate, audioCallback as dataCallback function, 
        setting correct mic input device
        returns false if error in setup occured, returns true otherwise
        */    

        bool startLiveCapture(ma_uint32 deviceIndex = 0);

        //ma_device cleanup 

        void stopLiveCapture();

        //Audio state:
        LiveCapture capture_;

        //ROS2 variables
        rclcpp::TimerBase::SharedPtr publish_timer_;
        rclcpp::Publisher<speech_to_text_interfaces::msg::AudioStamped>::SharedPtr publisher_;
    
}; //AudioCaptureNode{} class end


//WAV loader

/*
loads a WAV file from filename/filepath and pushes into samples
return true if audio file was loaded into samples, returns false otherwise
*/

bool loadWAV16kMonoF32(const char* filename, std::vector<float> &samples);









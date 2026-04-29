#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "audioCapture.hpp"




/*
The method we use for config.dataCallback when configuring the ma_device
Pushes each audio frame chunk to buffer (1 frame = 1 sample)
*/

static void audioCallback(ma_device* dev, void* output, const void* input, ma_uint32 frameCount);


// ---------------- LIVE MIC ----------------
ma_uint32 AudioCaptureNode::listDevices() {
    //initialize context and context_config
    ma_context context; 
    ma_context_config ctxConfig = ma_context_config_init();
    if (ma_context_init(nullptr, 0, &ctxConfig, &context) != MA_SUCCESS) {
        RCLCPP_FATAL(get_logger(), "listDevices: failed to init context");
        return 0;
    }
    //get the number of devices
    ma_uint32 captureDeviceCount;
    ma_device_info* captureInfos;
    ma_context_get_devices(&context, nullptr, 0, &captureInfos, &captureDeviceCount);

    ma_uint32 deviceIndex = 9;
    //loop through all of the devices, enumerate and print them out
    RCLCPP_INFO(get_logger(), "Available capture devices (%u):", captureDeviceCount); 
    for (ma_uint32 i = 0; i < captureDeviceCount; ++i) {
        RCLCPP_INFO(get_logger(), " [%u] %s", i, captureInfos[i].name);
        char deviceName[] = "SF-558 Mono";
        if(!std::strcmp(captureInfos[i].name, deviceName)) {
            deviceIndex = i;
        }
    }

    //cleanup
    ma_context_uninit(&context);
    return deviceIndex;
}

bool AudioCaptureNode::initContext() {
    ma_context_config cfg = ma_context_config_init();
    if (ma_context_init(nullptr, 0, &cfg, &capture_.context) != MA_SUCCESS) {
        RCLCPP_FATAL(get_logger(), "Failed to init miniaudio context");
        return false;
    }
    return true;
}


bool AudioCaptureNode::startLiveCapture(ma_uint32 deviceIndex) {
    ma_device_info* pInfos;
    ma_uint32 deviceCount;
    ma_context_get_devices(&capture_.context, nullptr, 0, &pInfos, &deviceCount);

    if (deviceIndex >= deviceCount) {
        RCLCPP_FATAL(get_logger(), "Device index %u is out of range (%u devices available)", deviceIndex, deviceCount);
        return false;
    }

    ma_device_config config = ma_device_config_init(ma_device_type_capture);
    config.capture.format   = ma_format_f32;
    config.capture.channels = NUM_CHANNELS; //we use mono channel for voice recording (no need fore stereo)
    config.sampleRate       = SAMPLE_RATE; 
    config.dataCallback     = audioCallback; //function used to get more data (audio samples)
    config.pUserData        = &capture_;
    config.capture.pDeviceID = &pInfos[deviceIndex].id; //configure usb mic device, index found from listDevices()

    if (ma_device_init(nullptr, &config, &capture_.device) != MA_SUCCESS) {
        RCLCPP_FATAL(get_logger(), "Failed to init capture device");
        return false;
    }

    if (ma_device_start(&capture_.device) != MA_SUCCESS) {
        RCLCPP_FATAL(get_logger(), "Failed to start capture device");
        ma_device_uninit(&capture_.device);
        return false;
    }

    RCLCPP_INFO(get_logger(), "Live recording started on device [%u]: %s", deviceIndex, pInfos[deviceIndex].name);
    return true;
}



void AudioCaptureNode::stopLiveCapture() {

    //cleanup
    ma_device_stop(&capture_.device);
    ma_device_uninit(&capture_.device);
    ma_context_uninit(&capture_.context);
}

void AudioCaptureNode::publishAudio() {
    const size_t available = capture_.buffer.size();
    if(available < SAMPLES_PER_CHUNK) {
        //Buffer doesn't have one chunk yet, skip this tick
        return;
    }

    //Drain one 20ms chunk
    /*
    If timer is late and >320 samples accumulated we still publish exactly one chunk
    to keep downstreem latency predictable. The next tick will be the remainder
    */
    auto msg = std::make_unique<speech_to_text_interfaces::msg::AudioStamped>();
    msg->sample_rate = SAMPLE_RATE;
    msg->channels = NUM_CHANNELS;
    msg->data = capture_.buffer.pop(SAMPLES_PER_CHUNK);
    msg->has_speech = vad_.detectSpeech(msg->data.data(), SAMPLES_PER_CHUNK);


    audioPublisher_->publish(std::move(msg));

    //DEBUG
    //RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Audio Capture Running");
    
}


void audioCallback(ma_device* device, void*, const void* input, ma_uint32 frameCount) {

    LiveCapture* capture = static_cast<LiveCapture*>(device->pUserData);
    if (!input || !capture) {
        return; //input or data coming in
    } 

    const float* in = static_cast<const float*>(input);
    capture->buffer.push(in, frameCount);

    // std::cout << "[DEBUG] | Buffer size: " << capture->buffer.size() << "\n";
}

// ---------------- WAV LOADER ----------------

bool loadWAV16kMonoF32(const char* filename, std::vector<float> &samples) {

    ma_decoder decoder;
    //configure decoder with f32, mono channel, 16000 sample rate 
    ma_decoder_config config = ma_decoder_config_init(ma_format_f32, 1, 16000);  

    if (ma_decoder_init_file(filename, &config, &decoder) != MA_SUCCESS) {
        std::cerr << "Failed to open WAV: " << filename << std::endl;
        return false;
    }


    //set size of vector
    ma_uint64 frameCount = 0;
    ma_decoder_get_length_in_pcm_frames(&decoder, &frameCount);
    samples.resize(frameCount);


    //put data into vector
    ma_uint64 framesRead = 0;
    ma_decoder_read_pcm_frames(&decoder, samples.data(), frameCount, &framesRead);

    //cleanup
    ma_decoder_uninit(&decoder);

    if (framesRead == 0) {
        std::cerr << "Failed to read WAV data" << std::endl;
        return false;
    }

    return true;
}


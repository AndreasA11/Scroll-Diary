#include "audio.hpp"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

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
    ma_uint64 frameCount;
    ma_decoder_get_length_in_pcm_frames(&decoder, &frameCount);
    samples.resize(frameCount);


    //put data into vector
    ma_uint64 framesRead;
    ma_decoder_read_pcm_frames(&decoder, samples.data(), frameCount, &framesRead);
    //cleanup
    ma_decoder_uninit(&decoder);

    if (framesRead == 0) {
        std::cerr << "Failed to read WAV data" << std::endl;
        return false;
    }

    return true;
}

// ---------------- LIVE MIC ----------------
void listDevices() {
    //initialize context and context_config
    ma_context context; 
    ma_context_config ctxConfig = ma_context_config_init();
    if (ma_context_init(nullptr, 0, &ctxConfig, &context) != MA_SUCCESS) {
        std::cerr << "Failed to init audio context\n";
        return;
    }

    //get the number of devices
    ma_uint32 captureDeviceCount;
    ma_device_info* captureInfos;
    ma_context_get_devices(&context, nullptr, 0, &captureInfos, &captureDeviceCount);

    //loop through all of the devices, enumerate and print them out
    std::cout << "Available capture devices:\n";
    for (ma_uint32 i = 0; i < captureDeviceCount; ++i) {
        std::cout << "  " << i << ": " << captureInfos[i].name << "\n";
    }

    //cleanup
    ma_context_uninit(&context);
}



void audioCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount)
{
    LiveCapture* capture = (LiveCapture*)device->pUserData;
    if (!input || !capture) {
        return; //input or data coming in
    } 
    
    const float* in = (const float*)input;
    capture->buffer.push(in, frameCount);

    // std::cout << "[DEBUG] | Buffer size: " << capture->buffer.size() << "\n";
}

bool startLiveCapture(LiveCapture &capture, ma_uint32 deviceIndex) {
    ma_device_info* pInfos;
    ma_uint32 deviceCount;
    ma_context_get_devices(&capture.context, nullptr, 0, &pInfos, &deviceCount);

    if (deviceIndex >= deviceCount) {
        std::cerr << "Invalid capture device index\n";
        return false;
    }

    ma_device_config config = ma_device_config_init(ma_device_type_capture);
    config.capture.format   = ma_format_f32;
    config.capture.channels = 1; //we use mono channel for voice recording (no need fore stereo)
    config.sampleRate       = 16000; //chunk of 1 second
    config.dataCallback     = audioCallback; //function used to get more data (audio samples)
    config.pUserData        = &capture;
    config.capture.pDeviceID = &pInfos[deviceIndex].id; //configure usb mic device, index found from listDevices()

    if (ma_device_init(nullptr, &config, &capture.device) != MA_SUCCESS) {
        std::cerr << "Failed to init capture device\n";
        return false;
    }

    if (ma_device_start(&capture.device) != MA_SUCCESS) {
        std::cerr << "Failed to start capture device\n";
        ma_device_uninit(&capture.device);
        return false;
    }

    std::cout << "Live recording started on device: " << pInfos[deviceIndex].name << "\n";
    return true;
}

void stopLiveCapture(LiveCapture &capture) {
    //cleanup
    ma_device_stop(&capture.device);
    ma_device_uninit(&capture.device);
}


#include "audio.hpp"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

// ---------------- WAV LOADER ----------------
bool loadWAV16kMonoF32(const char* filename, std::vector<float> &samples) {
    ma_decoder decoder;
    ma_decoder_config config = ma_decoder_config_init(ma_format_f32, 1, 16000);

    if (ma_decoder_init_file(filename, &config, &decoder) != MA_SUCCESS) {
        std::cerr << "Failed to open WAV: " << filename << std::endl;
        return false;
    }

    ma_uint64 frameCount;
    ma_decoder_get_length_in_pcm_frames(&decoder, &frameCount);
    samples.resize(frameCount);

    ma_uint64 framesRead;
    ma_decoder_read_pcm_frames(&decoder, samples.data(), frameCount, &framesRead);
    ma_decoder_uninit(&decoder);

    if (framesRead == 0) {
        std::cerr << "Failed to read WAV data" << std::endl;
        return false;
    }

    return true;
}

// ---------------- LIVE MIC ----------------
void audioCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount)
{
    LiveCapture* capture = (LiveCapture*)device->pUserData;
    if (!input || !capture) return;

    // Cast input to float pointer
    const float* in = (const float*)input;

    // FIXED: Don't multiply by channels since we're already mono (1 channel)
    // Each frame is 1 sample for mono audio
    capture->buffer.push(in, frameCount);

    // Optional: reduce console spam in production
    // std::cout << "Buffer size: " << capture->buffer.size() << "\n";
}

void listDevices() {
    ma_context context; 
    ma_context_config ctxConfig = ma_context_config_init();
    if (ma_context_init(nullptr, 0, &ctxConfig, &context) != MA_SUCCESS) {
        std::cerr << "Failed to init audio context\n";
        return;
    }

    ma_uint32 captureDeviceCount;
    ma_device_info* captureInfos;
    ma_context_get_devices(&context, nullptr, 0, &captureInfos, &captureDeviceCount);

    std::cout << "Available capture devices:\n";
    for (ma_uint32 i = 0; i < captureDeviceCount; ++i) {
        std::cout << "  " << i << ": " << captureInfos[i].name << "\n";
    }

    ma_context_uninit(&context);
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
    config.capture.channels = 1;
    config.sampleRate       = 16000;
    config.dataCallback     = audioCallback;
    config.pUserData        = &capture;
    config.capture.pDeviceID = &pInfos[deviceIndex].id;

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
    ma_device_stop(&capture.device);
    ma_device_uninit(&capture.device);
}


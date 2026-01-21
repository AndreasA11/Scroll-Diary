#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <mutex>
#include <atomic>
#include "miniaudio.h"
#include "circularBuffer.hpp"

struct LiveCapture {
    ma_context context;
    ma_device device;
    CircularBuffer<float> buffer;
    LiveCapture(size_t bufCapacity = 4 * 160000) : buffer(bufCapacity) {}
};

//WAV loader
bool load_wav_16k_mono_f32(const char* filename, std::vector<float> &samples);

//Live capture functions
void list_devices();
static void audio_callback(ma_device* dev, void* output, const void* input, ma_uint32 frameCount);
bool startLiveCapture(LiveCapture &capture, ma_uint32 deviceIndex = 0);
void stopLiveCapture(LiveCapture &capture);
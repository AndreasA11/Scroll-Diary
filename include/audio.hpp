#pragma once

#include "miniaudio.h"
#include "circularBuffer.hpp"

struct LiveCapture {
    ma_context context; 
    ma_device device;
    CircularBuffer<float> buffer; //circular buffer where audio samples are pushed into
    LiveCapture(size_t bufCapacity = 4 * 240000) : buffer(bufCapacity) {}  //1 minute of audio time in buffer
};

//WAV loader

/*
loads a WAV file from filename/filepath and pushes into samples

return true if audio file was loaded into samples, returns false otherwise
*/
bool loadWAV16kMonoF32(const char* filename, std::vector<float> &samples);

//Live capture functions

/*
Enumerates and prints all available audio capture devices on the system
Used to see which device to connect to in startLiveCapture
*/
void listDevices();

/*
The method we use for config.dataCallback when configuring the ma_device
Pushes each audio frame chunk to buffer (1 frame = 1 sample)
*/
static void audioCallback(ma_device* dev, void* output, const void* input, ma_uint32 frameCount);

/*
configuring ma_device, ma_format_f32, mono channel, 
16000 sample rate, audioCallback as dataCallback function, 
setting correct mic input device

returns false if error in setup occured, returns true otherwise
*/
bool startLiveCapture(LiveCapture &capture, ma_uint32 deviceIndex = 0);


//ma_device cleanup 
void stopLiveCapture(LiveCapture &capture);

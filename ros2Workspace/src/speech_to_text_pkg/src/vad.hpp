#pragma once
#include <vector>
#include <cmath>
#include <algorithm>


class LightweightVAD {
private:
    float noiseFloor;
    float speechMultiplier;
    float noiseAdaptRate;
    
    float zcr_threshold;      // Zero-crossing rate
    int minSpeechFrames;      // Min consecutive frames to confirm speech
    int speechFrameCount;
    
public:
    LightweightVAD(float noiseFloorIn = 0.001f, float noiseAdaptRateIn = 0.01f,
        float speechMultiplierIn = 4.0f, float zcrThresh = 0.3f, int minFrames = 3)
        : noiseFloor(noiseFloorIn), noiseAdaptRate(noiseAdaptRateIn), 
        speechMultiplier(speechMultiplierIn), zcr_threshold(zcrThresh), 
          minSpeechFrames(minFrames), speechFrameCount(0) {}

    //no copying
    LightweightVAD(const LightweightVAD&) = delete;
    LightweightVAD& operator=(const  LightweightVAD&) = delete;
    
    // Fast energy-based detection (~0.01ms for 320 samples)
    bool detectSpeech(const float* samples, size_t len) {
        if(len == 0) {
            return false;
        }
        
        // 1. Calculate RMS energy
        

        float energy = 0.0f;
        for(size_t i = 0; i < len; i++) {
            energy += samples[i] * samples[i];
        }
        energy = std::sqrt(energy / len);        
        // 2. Calculate zero-crossing rate (distinguishes speech from noise)
        int zeroCrossings = 0;
        for(size_t i = 1; i < len; i++) {
            if((samples[i] >= 0 && samples[i-1] < 0) || 
               (samples[i] < 0 && samples[i-1] >= 0)) {
                zeroCrossings++;
            }
        }
        float zcr = static_cast<float>(zeroCrossings) / (len - 1);
        
        // 3. Speech detection logic
        bool isSpeech = (energy > noiseFloor * speechMultiplier) && (zcr > zcr_threshold);
        if(!isSpeech) {
            noiseFloor = (1.0f - noiseAdaptRate) * noiseFloor + noiseAdaptRate * energy;
        }
        noiseFloor = std::max(noiseFloor, 1e-6f);
        // 4. Require multiple consecutive frames (reduce spurious triggers)
        if(isSpeech) {
            speechFrameCount++;
        } else {
            speechFrameCount = 0;
        }
        
        return speechFrameCount >= minSpeechFrames;
    }
    
    // Reset state
    void reset() {
        speechFrameCount = 0;
    }
};
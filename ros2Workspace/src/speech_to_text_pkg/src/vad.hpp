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
    int minSilenceFrames_;      // Min consecutive frames to confirm silence
    int speechFrameCount_;
    int silenceFrameCount_;
    
public:
    LightweightVAD(float noiseFloorIn = 0.01f, float noiseAdaptRateIn = 0.01f,
        float speechMultiplierIn = 2.0f, float zcrThresh = 0.05f, int minFrames = 1)
        : noiseFloor(noiseFloorIn), noiseAdaptRate(noiseAdaptRateIn), 
        speechMultiplier(speechMultiplierIn), zcr_threshold(zcrThresh), 
          minSilenceFrames_(minFrames), speechFrameCount_(0), silenceFrameCount_(0) {}

    //no copying
    LightweightVAD(const LightweightVAD&) = delete;
    LightweightVAD& operator=(const  LightweightVAD&) = delete;
    
    // Fast energy-based detection (~0.01ms for 320 samples)
    bool detectSpeech(const float* samples, size_t len) {
        if(len < 2) {  
            return false;
        }
        
        // 1. Calculate RMS energy
        
        double energyAccum = 0.0;
        for(size_t i = 0; i < len; i++) {
            energyAccum += static_cast<double>(samples[i]) * samples[i];
        }
        float energy = std::sqrt(static_cast<float>(energyAccum / len));        
        // 2. Calculate zero-crossing rate (distinguishes speech from noise)
        int zeroCrossings = 0;
        for(size_t i = 1; i < len; i++) {
            if((samples[i] >= 0 && samples[i-1] < 0) || 
               (samples[i] < 0 && samples[i-1] >= 0)) {
                zeroCrossings++;
            }
        }
        float zcr = 0.0f;
        if(len > 1) {
            zcr = static_cast<float>(zeroCrossings) / (len - 1);
        }
    
        // 3. Speech detection logic
        bool isSpeech = (energy > noiseFloor * speechMultiplier) && (zcr > zcr_threshold);
    
        if(!isSpeech) {
            noiseFloor = (1.0f - noiseAdaptRate) * noiseFloor + noiseAdaptRate * energy;
            silenceFrameCount_++;
            speechFrameCount_ = 0;
        } else {
            speechFrameCount_++;
            silenceFrameCount_ = 0;
        }

        noiseFloor = std::max(noiseFloor, 1e-6f);

        // Speech is confirmed immediately — one frame is enough
        // Silence requires minSilenceFrames consecutive frames to avoid mid-word gaps
        if(speechFrameCount_ > 0) return true;
        return silenceFrameCount_ >= minSilenceFrames_;
    }
    
    // Reset state
    void reset() {
        speechFrameCount_ = 0;
    }
};
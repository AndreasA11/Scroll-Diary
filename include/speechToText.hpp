#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <queue>
#include <condition_variable>
#include "whisper.h"
#include "audio.hpp"
#include "transcription.hpp"
#include "circularBuffer.hpp"

// Thread-safe queue for audio chunks
template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mtx;
    std::condition_variable cv;

public:
    void push(T item) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            queue.push(std::move(item));
        }
        cv.notify_one();
    }

    bool pop(T& item, int timeout_ms = -1) {
        std::unique_lock<std::mutex> lock(mtx);
        
        if(timeout_ms < 0) {
            // Wait indefinitely
            cv.wait(lock, [this]{ return !queue.empty(); });
        } else {
            // Wait with timeout
            if(!cv.wait_for(lock, std::chrono::milliseconds(timeout_ms), 
                           [this]{ return !queue.empty(); })) {
                return false; // timeout
            }
        }
        
        item = std::move(queue.front());
        queue.pop();
        return true;
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.size();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }
};

class SpeechToTextManager {
private:
    whisper_context *ctx;
    LiveCapture capture;

    // Threading
    std::thread chunkerThread;
    std::thread processorThread;
    std::atomic<bool> running;

    // Queue for audio chunks
    ThreadSafeQueue<std::vector<float>> chunkQueue;

    // Thread functions
    void chunkerThreadFunc();
    void processorThreadFunc();

public:
    explicit SpeechToTextManager(const std::string &modelPath);
    ~SpeechToTextManager();

    // WAV file
    bool STTMloadWAVfile(const std::string &filename);

    // Live audio
    bool STTMstartLiveCapture(ma_uint32 deviceIndex = 0);
    void STTMstopLiveCapture();
    void STTMwaitForShutdown();
};


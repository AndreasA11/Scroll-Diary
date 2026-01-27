#pragma once

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
    //push data into queue
    void push(T&& item) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            queue.push(std::move(item));
        }
        cv.notify_one();
    }

    //pop data from queue, return true if queue found chunk in timeoutMs ms
    bool pop(T& item, int timeoutMs = -1) {
        std::unique_lock<std::mutex> lock(mtx);
        
        if(timeoutMs < 0) {
            // Wait indefinitely
            cv.wait(lock, [this]{ return !queue.empty(); });
        } else {
            // Wait with timeout
            if(!cv.wait_for(lock, std::chrono::milliseconds(timeoutMs), 
                           [this]{ return !queue.empty(); })) {
                return false; // timeout
            }
        }
        
        item = std::move(queue.front());
        queue.pop();
        return true;
    }

    //gets the size of the queue
    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.size();
    }

    //returns true if queue is empty, false otherwise
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

    //CTOR:Initializes a whisper_context with modelPath, initializes other member variables
    explicit SpeechToTextManager(const std::string &modelPath);
    //DTOR: Normal whisper cleanup
    ~SpeechToTextManager();

    // WAV file
    //Transcribe an audio WAV file and print the transcription to std::cout
    bool STTMloadWAVfile(const std::string &filename);

    // Live audio

    /*
      Starts the live capture process, this is what handles the chunk  
      and processor threads in order to transcribe live audio. 
    */  
    bool STTMstartLiveCapture(ma_uint32 deviceIndex = 0);

    //live audio cleanup
    //Manage any leftover threads or loose ends and stop the live capture
    void STTMstopLiveCapture();
    //Waits for chunker and process thread to complete, then joins them
    void STTMwaitForShutdown();
};


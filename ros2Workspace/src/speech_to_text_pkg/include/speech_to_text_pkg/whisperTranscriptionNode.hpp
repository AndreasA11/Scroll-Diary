#include "rclcpp/rclcpp.hpp"
#include "speech_to_text_interfaces/msg/audio_stamped.hpp"
#include "circularBuffer.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/bool.hpp"
#include "rmw/qos_profiles.h"
#include <string>
#include <iostream>
#include "whisper.h"
#include <queue>

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



class whisperTranscriptionNode : public rclcpp::Node {
    private:

        bool liveCapture();

        //transcribe an audio chunk and return as a std::string
        std::string transcribeBuffer(std::vector<float>& samples);
        
        void cleanUpNode();

        bool whisperInit(std::string &modelPath);

        void publishTranscription(const std::string &transcribedChunk);

        void publishState();

        void transcriptionWorker();

        void audioCallback(
            const speech_to_text_interfaces::msg::AudioStamped::SharedPtr msg);

        std::atomic<bool> running_;
        std::thread transcriptionThread_;
        std::atomic<bool> transcriptionState_;
        //whisper context
        whisper_context *ctx_;
        whisper_context_params cparams_;

        // Queue for audio chunks
        ThreadSafeQueue<std::vector<float>> chunkQueue_;

        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr transcriptionPublisher_;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr transcriptionStatePublisher_;
        rclcpp::Subscription<speech_to_text_interfaces::msg::AudioStamped>::SharedPtr cleanedAudioSubscriber_;
        

    public:
        explicit whisperTranscriptionNode();
        ~whisperTranscriptionNode() override;
};
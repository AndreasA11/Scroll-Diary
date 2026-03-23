#include "whisperTranscriptionNode.hpp"

whisperTranscriptionNode::whisperTranscriptionNode()
: Node("whisper_transcription_node") {
    ctx_ = nullptr;
    running_.store(false);
    transcriptionState_.store(false);
    // ros2 run your_pkg whisper_node --ros-args -p model_path:=/path/to/model.bin

    this->declare_parameter<std::string>("model_path", "");
    std::string modelPath = this->get_parameter("model_path").as_string();
    
    if(!whisperInit(modelPath)) {
        RCLCPP_FATAL(get_logger(), "unable to initialize whisper context");
        exit(1);
    }

    if(modelPath.empty()) {
        RCLCPP_FATAL(get_logger(), "model_path parameter is required");
        throw std::runtime_error("model_path parameter not provided");
    }

    rclcpp::QoS audio_qos(rclcpp::KeepLast(10));
    audio_qos.best_effort();
    
    transcriptionPublisher_ = create_publisher<std_msgs::msg::String>("/transcription", 10);

    transcriptionStatePublisher_ = create_publisher<std_msgs::msg::Bool>("/transcriptionState", 10);

    cleaned_audio_subscriber_ = create_subscription<speech_to_text_interfaces::msg::AudioStamped>(
        "/whisper_audio", rclcpp::QoS(10).best_effort(), 
        std::bind(&whisperTranscriptionNode::audioCallback, this, std::placeholders::_1));

    RCLCPP_INFO(get_logger(), "[INFO] Whisper model loaded successfully");

    liveCapture();
}

whisperTranscriptionNode::~whisperTranscriptionNode() {
    cleanUpNode();
    if(ctx_) {
        whisper_free(ctx_);
        ctx_ = nullptr;
    }

}

bool whisperTranscriptionNode::whisperInit(std::string &modelPath) {
    cparams_ = whisper_context_default_params();
    ctx_ = whisper_init_from_file_with_params(modelPath.c_str(), cparams_);
    if(!ctx_) {
        RCLCPP_FATAL(get_logger(), "Failed to load whisper model");
        return false;
    }
    return true;
}

std::string whisperTranscriptionNode::transcribeBuffer(std::vector<float>& samples) {
    if (samples.empty()) {
        return "";
    }
    

    std::string fullText = "";

    whisper_full_params params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
   
   // Initial prompt to discourage hallucination
    params.initial_prompt = "This is a clear voice recording.";

    params.n_threads = 4;
    params.print_progress = false;
    params.print_realtime = false;
    params.print_timestamps = false;
    params.print_special = false;

    params.language = "en"; //english
    params.translate = false;

    //improve accuracy
    params.no_context = false;  // Use context from previous chunks
    params.audio_ctx = 1500;    // keep between 1500-3000
    
    params.temperature = 0.0f;/*randomization, low temperature picks the top choice, 
                              high tempurature leads to picking choices that are 
                              not the top choice (randomization)
                             */
    params.suppress_blank = true; //suppress blank outputs

    int ret = whisper_full(ctx_, params, samples.data(), samples.size());
    if (ret != 0) {
        std::cerr << "Whisper inference failed" << std::endl;
        return "";
    }

    int n_segments = whisper_full_n_segments(ctx_);
    //loop through every segment, transcribe each segment and append to final string, then return final string
    for (int i = 0; i < n_segments; ++i) {
        const char* txt = whisper_full_get_segment_text(ctx_, i);
        if(txt) {
            fullText += txt; //append transcribed chunk onto full string
        }
    }
    
    samples.clear();
    return fullText;
}

void whisperTranscriptionNode::audioCallback(
    const speech_to_text_interfaces::msg::AudioStamped::SharedPtr msg) {
    chunkQueue_.push(std::vector<float>(msg->data.begin(), msg->data.end()));
    RCLCPP_INFO(get_logger(), "Chunk enqueued, queue depth: %zu", chunkQueue_.size());
}

bool whisperTranscriptionNode::liveCapture() {
    if(running_.load()) {
        RCLCPP_ERROR(get_logger(), "[WARN] Capture already running)");
        return false;
    }

    running_.store(true);
    transcriptionThread_ = std::thread(&whisperTranscriptionNode::transcriptionWorker, this);

    return true;

}

void whisperTranscriptionNode::publishState() {
    auto msg = std_msgs::msg::Bool();
    msg.data = transcriptionState_.load();
    transcriptionStatePublisher_->publish(msg);

    RCLCPP_INFO(get_logger(), "Publishing transcriptionState: %s",
        msg.data ? "true" : "false"
    );
}


void whisperTranscriptionNode::publishTranscription(const std::string &transcribedChunk) {
    RCLCPP_INFO(get_logger(), "Publishing '%s':", transcribedChunk.c_str());
    auto message = std_msgs::msg::String();
    message.data = transcribedChunk;
    transcriptionPublisher_->publish(message);
}

void whisperTranscriptionNode::transcriptionWorker() {
    RCLCPP_INFO(get_logger(), "[INFO] Processor thread started");
    transcriptionState_.store(true);
    publishState();
    
    
    while(running_.load() || !chunkQueue_.empty()) {
        std::vector<float> chunk;
        
        // Wait for chunk with timeout
        if(chunkQueue_.pop(chunk, 200)) {
            RCLCPP_INFO(get_logger(), "[PROCESSOR] Processing chunk: %zu samples", chunk.size());
            
            auto start = std::chrono::high_resolution_clock::now();
            std::string transcribedChunk = transcribeBuffer(chunk); //call to transcribe chunk
            publishTranscription(transcribedChunk);
            auto end = std::chrono::high_resolution_clock::now();
            
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            RCLCPP_INFO(get_logger(), "[PROCESSOR] Transcription took %ld ms", duration.count());
        }
    }
    
    RCLCPP_INFO(get_logger(), "Processor thread stopped");

    transcriptionState_.store(false);
    publishState();
}

void whisperTranscriptionNode::cleanUpNode() {
     if(!running_.load()) {
        return; // Already stopped
    }

    RCLCPP_INFO(get_logger(), "Stopping live capture...");
    
    // Signal threads to stop
    running_.store(false);

    if(transcriptionThread_.joinable()) {
        RCLCPP_INFO(get_logger(), "Waiting for processor thread...");
        transcriptionThread_.join();
    }

    // whisper_free_context_params(&cparams_);
    // transcriptionState_.store(false);
    // publishState();
    
    RCLCPP_INFO(get_logger(), "Stopped live capture!");
}





int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    try {
        rclcpp::spin(std::make_shared<whisperTranscriptionNode>());
    } catch (const std::exception& e) {
        RCLCPP_FATAL(rclcpp::get_logger("main"), "Fatal: %s", e.what());
        rclcpp::shutdown();
        return 1;
    }

    rclcpp::shutdown();
    return 0;
    
}






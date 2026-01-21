#include "speechToText.hpp"

constexpr size_t CHUNK_SIZE = 240000; // ~15 seconds at 16kHz
constexpr size_t MIN_CHUNK_SIZE = 16000; // ~1 second minimum

SpeechToTextManager::SpeechToTextManager(const std::string &modelPath) 
    : ctx(nullptr), running(false) {
    ctx = whisper_init_from_file(modelPath.c_str());
    if(!ctx) {
        throw std::runtime_error("Failed to load whisper model");
    }
    std::cerr << "[INFO] Whisper model loaded successfully\n";
}

SpeechToTextManager::~SpeechToTextManager() {
    STTMstopLiveCapture();
    if(ctx) {
        whisper_free(ctx);
        ctx = nullptr;
    }
}

// -------------------------------- WAV --------------------------------

bool SpeechToTextManager::STTMloadWAVfile(const std::string &filename) {
    std::vector<float> samples;
    if(!loadWAV16kMonoF32(filename.c_str(), samples)) {
        std::cerr << "[ERROR] WAV load failed\n";
        return false;
    }

    std::cerr << "[INFO] Loaded WAV samples: " << samples.size() << "\n";
    std::string transcribedFile = transcribe_buffer(ctx, samples);
    std::cout << transcribedFile << std::flush << std::endl;
    return true;
}

// ---------------------------- LIVE AUDIO ----------------------------

// Thread 1: Chunker - reads from circular buffer and creates chunks
void SpeechToTextManager::chunkerThreadFunc() {
    std::cerr << "[INFO] Chunker thread started\n";
    
    while(running.load()) {
        size_t bufferSize = capture.buffer.size();
        
        // If we have enough data, create a chunk
        if(bufferSize >= CHUNK_SIZE) {
            std::vector<float> chunk = capture.buffer.pop(CHUNK_SIZE);
            
            std::cerr << "[CHUNKER] Created chunk: " << chunk.size() 
                      << " samples, queue size: " << chunkQueue.size() << "\n";
            
            // Push to processing queue
            chunkQueue.push(std::move(chunk));
            
        } else {
            // Not enough data yet, sleep briefly
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    
    // Process remaining data before exit
    size_t remaining = capture.buffer.size();
    if(remaining >= MIN_CHUNK_SIZE) {
        std::vector<float> chunk = capture.buffer.pop(remaining);
        std::cerr << "[CHUNKER] Final chunk: " << chunk.size() << " samples\n";
        chunkQueue.push(std::move(chunk));
    }
    
    std::cerr << "[INFO] Chunker thread stopped\n";
}

// Thread 2: Processor - processes chunks with Whisper
void SpeechToTextManager::processorThreadFunc() {
    std::cerr << "[INFO] Processor thread started\n";
    
    while(running.load() || !chunkQueue.empty()) {
        std::vector<float> chunk;
        
        // Wait for chunk with timeout
        if(chunkQueue.pop(chunk, 200)) {
            std::cerr << "[PROCESSOR] Processing chunk: " << chunk.size() << " samples\n";
            
            auto start = std::chrono::high_resolution_clock::now();
            std::string transcribedChunk = transcribe_buffer(ctx, chunk);
            std::cout << transcribedChunk << std::flush << std::endl;
            auto end = std::chrono::high_resolution_clock::now();
            
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cerr << "[PROCESSOR] Transcription took " << duration.count() << "ms\n";
        }
    }
    
    std::cerr << "[INFO] Processor thread stopped\n";
}

bool SpeechToTextManager::STTMstartLiveCapture(ma_uint32 deviceIndex) {
    if(running.load()) {
        std::cerr << "[WARN] Capture already running\n";
        return false;
    }

    // Clear buffer
    capture.buffer.clear();

    // Initialize audio context
    ma_context_config ctxConfig = ma_context_config_init();
    if(ma_context_init(nullptr, 0, &ctxConfig, &capture.context) != MA_SUCCESS) {
        std::cerr << "[ERROR] Failed to init audio context\n";
        return false;
    }

    // Start capture device
    if(!startLiveCapture(capture, deviceIndex)) {
        std::cerr << "[ERROR] Failed to start live capture\n";
        ma_context_uninit(&capture.context);
        return false;
    }

    // Start threads
    running.store(true);
    chunkerThread = std::thread(&SpeechToTextManager::chunkerThreadFunc, this);
    processorThread = std::thread(&SpeechToTextManager::processorThreadFunc, this);

    std::cerr << "[INFO] Multi-threaded live capture started\n";
    std::cerr << "[INFO] - Audio capture: Running in callback\n";
    std::cerr << "[INFO] - Chunker thread: Running\n";
    std::cerr << "[INFO] - Processor thread: Running\n";
    
    return true;
}

void SpeechToTextManager::STTMstopLiveCapture() {
    if(!running.load()) {
        return; // Already stopped
    }

    std::cerr << "[INFO] Stopping live capture...\n";
    
    // Signal threads to stop
    running.store(false);

    // Stop audio capture first
    stopLiveCapture(capture);

    // Wait for threads to finish
    if(chunkerThread.joinable()) {
        std::cerr << "[INFO] Waiting for chunker thread...\n";
        chunkerThread.join();
    }
    
    if(processorThread.joinable()) {
        std::cerr << "[INFO] Waiting for processor thread...\n";
        processorThread.join();
    }

    // Cleanup audio context
    ma_context_uninit(&capture.context);

    std::cerr << "[INFO] Live capture stopped completely\n";
}

void SpeechToTextManager::STTMwaitForShutdown() {
    // Just wait for the threads to complete
    if(chunkerThread.joinable()) {
        chunkerThread.join();
    }
    if(processorThread.joinable()) {
        processorThread.join();
    }
}



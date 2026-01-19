#include "speechToText.hpp"
#include "audio.hpp"
#include <csignal>
#include <atomic>
#include <iostream>

std::atomic<bool> gRunning(true);
SpeechToTextManager* gSTT = nullptr;

void sigintHandler(int) {
    std::cout << "\n[INFO] Received interrupt signal, shutting down gracefully...\n";
    gRunning.store(false);
    if(gSTT) {
        gSTT->STTMstopLiveCapture();
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <model.bin> <wav|live> [filename if wav] [device_index if live]\n";
        std::cout << "\nExamples:\n";
        std::cout << "  WAV:  " << argv[0] << " model.bin wav audio.wav\n";
        std::cout << "  Live: " << argv[0] << " model.bin live 0\n";
        return 1;
    }

    std::string modelPath = argv[1];
    std::string mode = argv[2];

    try {
        SpeechToTextManager stt(modelPath);
        gSTT = &stt;
        signal(SIGINT, sigintHandler);

        if(mode == "live") {
            // List available devices
            std::cout << "\n=== Available Audio Devices ===\n";
            list_devices();
            std::cout << "================================\n\n";

            // Get device index
            ma_uint32 deviceIndex = 0;
            if(argc >= 4) {
                deviceIndex = std::stoi(argv[3]);
            }

            std::cout << "[INFO] Initializing multi-threaded speech-to-text system\n";
            std::cout << "[INFO] Using device index: " << deviceIndex << "\n";
            std::cout << "[INFO] Chunk size: 10 seconds\n";
            std::cout << "[INFO] Sample rate: 16kHz mono\n\n";

            // Start capture
            if(!stt.STTMstartLiveCapture(deviceIndex)) {
                std::cerr << "[ERROR] Failed to start live capture\n";
                return 1;
            }

            std::cout << "\n=== System Running ===\n";
            std::cout << "Speak into your microphone...\n";
            std::cout << "Press Ctrl+C to stop\n\n";

            // Main thread just waits
            while(gRunning.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }

            std::cout << "\n[INFO] Shutdown initiated\n";

        } else if(mode == "wav") {
            if(argc < 4) {
                std::cerr << "[ERROR] Please provide WAV filename\n";
                return 1;
            }
            
            std::string filename = argv[3];
            std::cout << "[INFO] Processing WAV file: " << filename << "\n";
            
            if(!stt.STTMloadWAVfile(filename)) {
                std::cerr << "[ERROR] Failed to process WAV file\n";
                return 1;
            }
            
        } else {
            std::cerr << "[ERROR] Unknown mode: " << mode << "\n";
            std::cerr << "Valid modes: wav, live\n";
            return 1;
        }

        std::cout << "[INFO] Program exiting normally\n";

    } catch(const std::exception& e) {
        std::cerr << "[FATAL ERROR] " << e.what() << "\n";
        return 1;
    }

    gSTT = nullptr;
    return 0;
}

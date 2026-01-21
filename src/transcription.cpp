#include "transcription.hpp"

std::string transcribe_buffer(whisper_context* ctx, std::vector<float>& samples) {
    if (samples.empty()) {
        return "";
    }
    

    std::string fullText = "";

    whisper_full_params params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
   
   // Initial prompt to discourage hallucination
    params.initial_prompt = "This is a clear voice recording.";
   
    params.print_progress = false;
    params.print_realtime = false;
    params.print_timestamps = true;
    params.print_special = false;

    params.n_threads = 4;
    params.print_progress = false;
    params.print_realtime = false;
    params.print_timestamps = false;
    params.print_special = false;

    //params.speed_up = true;
    params.language = "en";
    params.translate = false;

    // ACCURACY IMPROVEMENTS:
    params.no_context = false;  // Use context from previous chunks
    params.audio_ctx = 1500;    // Default value (more context = better accuracy)
    //params.beam_size = 5;       // Increase from 1 (slower but more accurate)
    //params.best_of = 5;         // Try 5 candidates (slower but more accurate)

    params.temperature = 0.0f;
    params.suppress_blank = true;
    //params.suppress_non_speech_tokens = true;

    int ret = whisper_full(ctx, params, samples.data(), samples.size());
    if (ret != 0) {
        std::cerr << "Whisper inference failed" << std::endl;
        return "";
    }

    int n_segments = whisper_full_n_segments(ctx);
    for (int i = 0; i < n_segments; ++i) {
        const char* txt = whisper_full_get_segment_text(ctx, i);
        if(txt) {
            fullText += txt;
        }
    }
    

    samples.clear();
    return fullText;
}


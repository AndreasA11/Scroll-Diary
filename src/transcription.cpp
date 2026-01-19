#include "transcription.hpp"

void transcribe_buffer(whisper_context* ctx, std::vector<float>& samples) {
    if (samples.empty()) return;

    whisper_full_params params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
    params.print_progress = false;
    params.print_realtime = false;
    params.print_timestamps = true;
    params.print_special = false;

    int ret = whisper_full(ctx, params, samples.data(), samples.size());
    if (ret != 0) {
        std::cerr << "Whisper inference failed" << std::endl;
        return;
    }

    int n_segments = whisper_full_n_segments(ctx);
    for (int i = 0; i < n_segments; ++i) {
        const char* txt = whisper_full_get_segment_text(ctx, i);
        std::cout << txt << std::flush;
    }
    std::cout << std::endl;

    samples.clear();
}


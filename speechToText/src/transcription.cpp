#include "transcription.hpp"

std::string transcribeBuffer(whisper_context* ctx, std::vector<float>& samples) {
    if (samples.empty()) {
        return "";
    }
    

    std::string fullText = "";

    whisper_full_params params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
   
   // Initial prompt to discourage hallucination
    params.initial_prompt = "This is a clear voice recording.";
   

    params.print_progress = false;
    params.print_realtime = false;
    params.print_timestamps = true; //for debug
    params.print_special = false;

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

    int ret = whisper_full(ctx, params, samples.data(), samples.size());
    if (ret != 0) {
        std::cerr << "Whisper inference failed" << std::endl;
        return "";
    }

    int n_segments = whisper_full_n_segments(ctx);
    //loop through every segment, transcribe each segment and append to final string, then return final string
    for (int i = 0; i < n_segments; ++i) {
        const char* txt = whisper_full_get_segment_text(ctx, i);
        if(txt) {
            fullText += txt; //append transcribed chunk onto full string
        }
    }
    
    samples.clear();
    return fullText;
}


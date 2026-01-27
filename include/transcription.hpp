#pragma once

#include "pch.hpp"
#include "whisper.h"

//transcribe audio samples and output as a std::string
std::string transcribeBuffer(whisper_context* ctx, std::vector<float>& samples);


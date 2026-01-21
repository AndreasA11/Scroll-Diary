#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "whisper.h"

std::string transcribe_buffer(whisper_context* ctx, std::vector<float>& samples);


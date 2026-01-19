cmake_minimum_required(VERSION 3.31)
project(speechToText VERSION 0.1.0 LANGUAGES C CXX)

option(WHISPER_NEON "whisper: use NEON" ON)
option(WHISPER_NO_AVX "whisper: disable AVX" ON)
option(WHISPER_NO_AVX2 "whisper: disable AVX2" ON)
option(WHISPER_NO_FMA "whisper: disable FMA" ON)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=armv8.2-a+fp16 -mtune=cortex-a76")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=armv8.2-a+fp16 -mtune=cortex-a76")
endif()


set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(whisperCXX)

add_executable(speechToText
    main.cpp
    src/audio.cpp
    src/transcription.cpp
    src/speechToText.cpp
)

target_include_directories(speechToText PRIVATE 
    include
    whisperCXX/include
    whisperCXX/examples
)


target_link_libraries(speechToText PRIVATE whisper)



include(CTest)
enable_testing()


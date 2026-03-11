cmake_minimum_required(VERSION 3.8)
project(speech_to_text_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(speech_to_text_interfaces REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)


add_executable(audio_capture_node 
  src/audioCaptureNode.cpp
  src/audioFunctions.cpp
  src/vad.hpp
)

ament_target_dependencies(
  audio_capture_node 
  rclcpp
  speech_to_text_interfaces
)

target_include_directories(audio_capture_node PRIVATE
  include/speech_to_text_pkg
  src
  libs
)

add_executable(transcription_pre_process_node
  src/whisperPreProcessNode.cpp
)

ament_target_dependencies(
  transcription_pre_process_node
  rclcpp
  speech_to_text_interfaces
  std_msgs
)

target_include_directories(transcription_pre_process_node PRIVATE
  include/speech_to_text_pkg
  src
)

add_executable(whisper_transcription_node
  src/whisperTranscriptionNode.cpp
)

include(FetchContent)

FetchContent_Declare(
  whisper
  GIT_REPOSITORY https://github.com/ggerganov/whisper.cpp.git
    GIT_TAG        v1.8.3  # pin a specific version
)

FetchContent_MakeAvailable(whisper)

target_link_libraries(whisper_transcription_node whisper)


ament_target_dependencies(
  whisper_transcription_node
  rclcpp
  speech_to_text_interfaces
  std_msgs
)

target_include_directories(whisper_transcription_node PRIVATE
  include/speech_to_text_pkg
  src
)

install(TARGETS
  transcription_pre_process_node
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS
  audio_capture_node
  DESTINATION lib/${PROJECT_NAME}  
)

install(TARGETS
  whisper_transcription_node
  DESTINATION lib/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/wakeWordNode.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

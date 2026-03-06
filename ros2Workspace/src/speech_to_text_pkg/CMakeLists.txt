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

install(TARGETS
  audio_capture_node
  DESTINATION lib/${PROJECT_NAME}  
)

install(PROGRAMS
  scripts/wakeWordNode.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

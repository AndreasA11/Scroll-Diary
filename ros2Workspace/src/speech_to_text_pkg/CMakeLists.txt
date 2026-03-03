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
find_packages(audio_samples_interfaces REQUIRED)

include_directories(include)


add_executable(audio_node src/audioNode.cpp)
ament_target_dependencies(audio_node 
  rclcpp
  audio_samples_interfaces
)

target_include_directories(audio_node PRIVATE
  include/speech_to_text_pkg
  libs
)

install(TARGETS
  audio_node
  DESTINATION lib/${PROJECT_NAME}  
)

install(PROGRAMS
  scripts/py_node.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

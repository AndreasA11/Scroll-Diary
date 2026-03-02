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

include_directories(include)



add_executable(minimal_cpp_node src/minimalNode1.cpp)
ament_target_dependencies(minimal_cpp_node rclcpp)

target_include_directories(minimal_cpp_node PRIVATE 
  include/speech_to_text_pkg)


install(TARGETS
  minimal_cpp_node
  DESTINATION lib/${PROJECT_NAME}  
)

install(PROGRAMS
  scripts/py_node.py
  DESTINATION lib/${PROJECT_NAME}
)

message(STATUS "Does script exist: ${CMAKE_CURRENT_SOURCE_DIR}/scripts/py_node.py")


ament_package()

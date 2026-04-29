cmake_minimum_required(VERSION 3.8)
project(printer_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)

add_executable(printing_node
  src/printingNode.cpp
)

ament_target_dependencies(
  printing_node
  rclcpp
  std_msgs
)

target_include_directories(printing_node PRIVATE
  include/printer_pkg
  src
)


ament_package()

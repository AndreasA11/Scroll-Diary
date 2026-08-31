cmake_minimum_required(VERSION 3.8)
project(motor_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(speech_to_text_pkg REQUIRED)
find_package(printer_pkg REQUIRED)

add_executable(motor_node
  src/motorControl.cpp)



include_directories(include)

ament_target_dependencies(
  motor_node
  rclcpp
  std_msgs
)

find_library(LGPIO_LIB NAMES lgpio REQUIRED)

target_link_libraries(motor_node ${LGPIO_LIB})

target_include_directories(motor_node PRIVATE
  include/motor_pkg
  src
)

install(TARGETS
  motor_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

cmake_minimum_required(VERSION 3.8)
project(tat_e0u_benya)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)

set(ament_dependencies
  rclcpp
  std_msgs
  geometry_msgs
)


add_executable(draw src/draw.cpp)
ament_target_dependencies(draw rclcpp geometry_msgs turtlesim)

install(TARGETS
  draw  
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})


ament_package()
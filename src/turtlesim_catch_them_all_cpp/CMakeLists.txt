cmake_minimum_required(VERSION 3.5)
project(turtlesim_catch_them_all_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(controller_cpp src/turtle_controller.cpp)
ament_target_dependencies(controller_cpp rclcpp turtlesim
geometry_msgs)

add_executable(spawner_cpp src/turtle_spawner.cpp)
ament_target_dependencies(spawner_cpp rclcpp turtlesim)

install(TARGETS
  controller_cpp
  spawner_cpp
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

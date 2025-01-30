cmake_minimum_required(VERSION 3.5)
project(my_cpp_pkg)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(my_robot_interfaces REQUIRED)

add_executable(cpp_node src/my_first_node.cpp)
ament_target_dependencies(cpp_node rclcpp)

add_executable(robot_news_station_cpp src/robot_news_station.cpp)
ament_target_dependencies(robot_news_station_cpp rclcpp example_interfaces)

add_executable(smartphone_cpp src/smartphone.cpp)
ament_target_dependencies(smartphone_cpp rclcpp example_interfaces)

add_executable(number_publisher_cpp src/number_publisher.cpp)
ament_target_dependencies(number_publisher_cpp rclcpp example_interfaces)

add_executable(number_counter_cpp src/number_counter.cpp)
ament_target_dependencies(number_counter_cpp rclcpp example_interfaces)

add_executable(add_two_ints_server_cpp src/add_two_ints_server.cpp)
ament_target_dependencies(add_two_ints_server_cpp rclcpp example_interfaces)

add_executable(add_two_ints_client_no_oop src/add_two_ints_client_no_oop.cpp)
ament_target_dependencies(add_two_ints_client_no_oop rclcpp example_interfaces)

add_executable(add_two_ints_client src/add_two_ints_client.cpp)
ament_target_dependencies(add_two_ints_client rclcpp example_interfaces)

add_executable(number_counter_server_cpp src/number_counter_server.cpp)
ament_target_dependencies(number_counter_server_cpp rclcpp example_interfaces)

add_executable(reset_number_client src/reset_number_client.cpp)
ament_target_dependencies(reset_number_client rclcpp example_interfaces)

add_executable(hardware_status_publisher_cpp src/hw_status_publisher.cpp)
ament_target_dependencies(hardware_status_publisher_cpp rclcpp my_robot_interfaces)

add_executable(led_panel_cpp src/led_panel.cpp)
ament_target_dependencies(led_panel_cpp rclcpp my_robot_interfaces)

install(TARGETS
  cpp_node
  robot_news_station_cpp
  smartphone_cpp
  number_publisher_cpp
  number_counter_cpp
  add_two_ints_server_cpp
  add_two_ints_client_no_oop
  add_two_ints_client
  number_counter_server_cpp
  reset_number_client
  hardware_status_publisher_cpp
  led_panel_cpp
  DESTINATION lib/${PROJECT_NAME}

)

ament_package()

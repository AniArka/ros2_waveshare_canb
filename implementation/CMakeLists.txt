cmake_minimum_required(VERSION 3.10)
project(implementation)

set(CMAKE_CXX_STANDARD 14)

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(usb_can_node REQUIRED)

add_executable(test_send src/test.cpp)

ament_target_dependencies(test_send
  rclcpp
  usb_can_node
)

target_link_directories(test_send PUBLIC
  ${usb_can_node_DIR}/../../../lib
)

target_link_libraries(test_send
  usb_can_utils
  ${CMAKE_SOURCE_DIR}/../usb_can_node/libcontrolcan.so
  pthread
)

install(TARGETS
  test_send
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

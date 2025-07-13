cmake_minimum_required(VERSION 3.10)
project(usb_can_node)

set(CMAKE_CXX_STANDARD 14)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

include_directories(
  include
  include/usb_can_node
)

add_library(usb_can_utils SHARED
  src/usb_can_utils.cpp
)


set_target_properties(usb_can_utils PROPERTIES EXPORT_NAME usb_can_utils)

target_include_directories(usb_can_utils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(usb_can_utils
  ${CMAKE_CURRENT_SOURCE_DIR}/libcontrolcan.so
  pthread
)

ament_target_dependencies(usb_can_utils rclcpp)

install(TARGETS
  usb_can_utils
  EXPORT export_usb_can_utils
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)


install(
  EXPORT export_usb_can_utils
  NAMESPACE usb_can_node::
  DESTINATION share/${PROJECT_NAME}/cmake
)

install(DIRECTORY include/
  DESTINATION include/
)

install(FILES libcontrolcan.so
  DESTINATION lib
)

ament_export_include_directories(include)
ament_export_libraries(usb_can_utils)


ament_export_targets(export_usb_can_utils HAS_LIBRARY_TARGET)

ament_package()


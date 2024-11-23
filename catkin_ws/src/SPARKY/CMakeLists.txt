cmake_minimum_required(VERSION 3.0.2)
project(SPARKY)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

## Declare a catkin package
catkin_package()

## Include directories
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Add the executable
add_executable(sparky_node
  src/main.cpp
  src/display.cpp
  src/motors.cpp
  src/sensors.cpp
)

## Link against catkin libraries
target_link_libraries(sparky_node
  ${catkin_LIBRARIES}
)

## Install targets
install(TARGETS sparky_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


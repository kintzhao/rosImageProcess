cmake_minimum_required(VERSION 2.8.3)
project(rosbag2img)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)
set(OpenCV_DIR /opt/ros/kinetic/include/opencv-3.3.1-dev/)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  rospy
  sensor_msgs
  std_msgs
  rosbag
)

find_package(OpenCV 3 REQUIRED)

catkin_package(
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_DIR}
)


add_executable(rosbag2img src/main.cpp)


## Specify libraries to link a library or executable target against
target_link_libraries(rosbag2img
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES}
)


add_executable(rosbag2video src/image2video.cpp)
target_link_libraries(rosbag2video
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES}
)

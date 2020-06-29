cmake_minimum_required(VERSION 2.8.3)
project(imageCapture)
 
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
)

find_package( OpenCV REQUIRED )

 
## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

catkin_package( )

message(STATUS ${OpenCV_INCLUDE_DIRS})
 
 
add_executable( ros2img src/image_transport_subscriber.cpp )
target_link_libraries ( ros2img ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} )

add_executable( ros2img_rs src/image_transport_subscriber_rs.cpp )
target_link_libraries ( ros2img_rs ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} )

add_executable( img2ros src/image_transport_publisher.cpp )
target_link_libraries ( img2ros ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} )

cmake_minimum_required(VERSION 2.8)
project( best_filter_video_webcam )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( best_filter_video_webcam best_filter_video_webcam.cpp )
target_link_libraries( best_filter_video_webcam ${OpenCV_LIBS} )

cmake_minimum_required(VERSION 3.0.0)
project(add_filter_kernel3x3 VERSION 0.1.0)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

add_executable(add_filter_to_images add_filter_to_images.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX__STANDARD_REQUIRED ON)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(add_filter_to_images ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})

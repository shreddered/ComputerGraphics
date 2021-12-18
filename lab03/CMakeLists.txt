cmake_minimum_required(VERSION 3.15)

project(lab03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV COMPONENTS core highgui imgcodecs REQUIRED)

add_executable(lab03
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sobel.cpp
)

target_include_directories(lab03
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(lab03
  PRIVATE opencv_core opencv_highgui opencv_imgcodecs
)

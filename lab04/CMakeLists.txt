cmake_minimum_required(VERSION 3.15)

project(lab04)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV COMPONENTS core highgui REQUIRED)

add_executable(lab04
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/bezier.cpp
)

target_include_directories(lab04
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(lab04
  PRIVATE opencv_core opencv_highgui
)

cmake_minimum_required(VERSION 3.15)

project(lab01)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV COMPONENTS core highgui REQUIRED)
find_package(Threads REQUIRED)

add_executable(lab01
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/bresenham.cpp
)

target_include_directories(lab01
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(lab01
  PRIVATE opencv_core opencv_highgui Threads::Threads
)

cmake_minimum_required(VERSION 3.15)

project(lab06)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
string(APPEND CMAKE_CXX_FLAGS " -g")

find_package(OpenCV COMPONENTS core highgui REQUIRED)

add_executable(lab06
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/bezier.cpp
)

target_include_directories(lab06
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(lab06
  PRIVATE opencv_core opencv_highgui
)

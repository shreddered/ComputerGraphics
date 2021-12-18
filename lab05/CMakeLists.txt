cmake_minimum_required(VERSION 3.15)

project(lab05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
string(APPEND CMAKE_CXX_FLAGS " -g")

find_package(OpenCV COMPONENTS core highgui REQUIRED)

add_executable(lab05
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/fill.cpp
)

target_include_directories(lab05
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(lab05
  PRIVATE opencv_core opencv_highgui
)

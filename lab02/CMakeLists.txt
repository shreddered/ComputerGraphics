cmake_minimum_required(VERSION 3.15)

project(lab02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV COMPONENTS core highgui REQUIRED)

add_executable(lab02
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/cyrus_beck.cpp
)

target_include_directories(lab02
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(lab02
  PRIVATE opencv_core opencv_highgui
)

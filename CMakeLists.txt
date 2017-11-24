cmake_minimum_required(VERSION 3.8)
project(viagogo_coding_challenge)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp event.cpp event.h event_plane.cpp event_plane.h)
add_executable(viagogo_coding_challenge ${SOURCE_FILES} event.cpp event.h)
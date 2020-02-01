cmake_minimum_required(VERSION 3.0)

# configure the compiler before naming project
# Using mingw g++ toolchains in windows platform
# compile path using Unix format, not windows(Parsing string error when doing cmake)
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")


project(OpenGL
    VERSION 0.1
    DESCRIPTION "learning OpenGL and practising"
    LANGUAGES CXX)

# For debuging CMake
message(${CMAKE_CXX_COMPILER})

# For global compile options
list(APPEND CMAKE_CXX_FLAGS "-g -std=c++11" ${CMAKE_CXX_FLAGS})

# add include dirs path
include_directories(./include)

# Add a list of subdirectories to the build.
add_subdirectory(glwindow)
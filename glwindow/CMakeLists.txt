cmake_minimum_required(VERSION 3.0)

project(glwindow)

# For collecting the source code files
aux_source_directory(. SRC)

# static library
# add_library(glwindow STATIC ${SRC})

# for test
add_executable(glwindow ${SRC})

target_link_libraries(glwindow glfw3 pthread glprogram)
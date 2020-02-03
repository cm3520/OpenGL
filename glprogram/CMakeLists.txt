cmake_minimum_required(VERSION 3.0)

project(glprogram)

# For collecting the source code files
aux_source_directory(. SRC)

# static library
 add_library(glprogram STATIC ${SRC})
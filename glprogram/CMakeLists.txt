cmake_minimum_required(VERSION 3.0)

project(glprogram)

# For collecting the source code files
aux_source_directory(. SRC)

link_directories("../libs")

# static library
 add_library(glprogram STATIC ${SRC})

 target_link_libraries(glprogram glew32s glu32 opengl32 SOIL)
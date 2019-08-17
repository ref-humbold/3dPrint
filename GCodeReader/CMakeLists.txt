cmake_minimum_required(VERSION 3.5)
project(GCodeReader VERSION 1.0)

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas")

# SOURCES
include_directories(include)
set(SOURCES
    src/gcode.cpp
    src/parameters.cpp
    src/uart_ctrl.cpp
    src/parser.cpp
    src/instructions.cpp
    src/instruction_list.cpp
    src/file_reader.cpp
    src/vec.cpp)

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
add_executable(gcode ${SOURCES})

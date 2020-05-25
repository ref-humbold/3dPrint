cmake_minimum_required(VERSION 3.10)

# SOURCES
set(SOURCES
    file_reader.cpp
    gcode.cpp
    parameters.cpp
    parser.cpp
    uart_ctrl.cpp
    vec.cpp)

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXE_OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LIB_OUTPUT_DIR}")
add_library(gcodeLib SHARED ${SOURCES})
add_executable(gcode ${SOURCES})

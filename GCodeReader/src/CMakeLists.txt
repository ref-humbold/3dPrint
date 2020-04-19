cmake_minimum_required(VERSION 3.10)

# SOURCES
set(SOURCES
    "file_reader.cpp"
    "gcode.cpp"
    "instruction_list.cpp"
    "instructions.cpp"
    "parameters.cpp"
    "parser.cpp"
    "uart_ctrl.cpp"
    "vec.cpp")

# TESTS
include(CTest)

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/dist")
add_library(gcodeLib SHARED ${SOURCES})
add_executable(gcode ${SOURCES})

cmake_minimum_required(VERSION 3.5)
project(GCodeReader VERSION 1.0)

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas")

# SOURCES
include_directories("${PROJECT_SOURCE_DIR}/include")
set(SOURCES "${PROJECT_SOURCE_DIR}/src/parameters.cpp"
            "${PROJECT_SOURCE_DIR}/src/uart_ctrl.cpp"
            "${PROJECT_SOURCE_DIR}/src/gcode.cpp")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
add_executable(gcode ${SOURCES})

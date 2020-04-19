cmake_minimum_required(VERSION 3.10)
project(GCodeReader VERSION 0.0)

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas")

# SOURCES
include_directories(include)

# TESTS
include(CTest)

# OUTPUT
add_subdirectory(src)
add_subdirectory(test)

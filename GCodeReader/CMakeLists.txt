cmake_minimum_required(VERSION 3.10)
project(GCodeReader VERSION 0.0)

# PROPERTIES
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/test")
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/buildOut")
set(EXE_OUTPUT_DIR "${OUTPUT_DIR}/bin")
set(LIB_OUTPUT_DIR "${OUTPUT_DIR}/dist")

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas -O2")

# PACKAGES
find_package(GTest)

# SOURCES
include_directories("${INCLUDE_DIR}")

# OUTPUT
add_subdirectory("${SRC_DIR}")

if(GTEST_FOUND)
    include(CTest)
    add_subdirectory("${TEST_DIR}")
endif()

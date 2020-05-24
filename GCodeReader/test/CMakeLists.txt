cmake_minimum_required(VERSION 3.10)

# PACKAGES
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_THREAD_PREFER_PTHREAD true)
set(THREADS_PREFER_PTHREAD_FLAG true)
find_package(Threads REQUIRED)

# SOURCES
set(SOURCES
    file_reader_test.cpp
    uart_test.cpp)

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXE_OUTPUT_DIR}/test")
foreach(testsource ${SOURCES})
    get_filename_component(testexec ${testsource} NAME_WE)
    add_executable(${testexec} ${testsource})
    target_link_libraries(${testexec}
                          GTest::GTest
                          "${LIB_OUTPUT_DIR}/libgcodeLib.so")
    gtest_add_tests(TARGET ${testexec})
endforeach(testsource ${SOURCES})

file(COPY resources DESTINATION "${EXE_OUTPUT_DIR}/test")

cmake_minimum_required(VERSION 3.27)

set(EXECUTABLE_NAME "c_cpp_examples")
message(STATUS "${EXECUTABLE_NAME}: build starting")

set(SOURCES c_cpp_examples.cpp
        DistanceMatrixReader.h
        DistanceMatrixWriter.h
        MemoryExample.cpp
        MemoryExample.h)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

#---------
message(STATUS "${EXECUTABLE_NAME}: build done")

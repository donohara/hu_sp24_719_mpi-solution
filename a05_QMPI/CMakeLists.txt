cmake_minimum_required(VERSION 3.27)

#---------
set(PROJECT_NAME a05_QMPI)
message(STATUS "${PROJECT_NAME}: starting")
#---------

project(${PROJECT_NAME})
set(SOURCES
        main.cpp
        QMPI.cpp
        QMPI.h
        MyMPI.h
        MyMPI.c
)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
# Make sure to use the MPI compiler wrappers: mpicc, mpicxx, etc.
set(CMAKE_CXX_COMPILER mpicxx)
# Include MPI includes
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${MPI_C_LIBRARIES})

#---------
message(STATUS "${PROJECT_NAME}: done")

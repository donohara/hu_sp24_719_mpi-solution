cmake_minimum_required(VERSION 3.27)

#---------
set(PROJECT_NAME mpi-sample)
message(STATUS "${PROJECT_NAME}: starting")
#---------

project(${PROJECT_NAME})
set(SOURCES
        Example_0.cpp
        Example_1.cpp
        Example_2.cpp
        Example_3.cpp
        Example_4.cpp
        Example_5.cpp
        floyds_algorithm.cpp
        mpi-sample.cpp
        quinn_mpi.cpp
        read_adjacency_matrix.cpp
#        sieve_of_eratosthenes_.cpp
)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
# Make sure to use the MPI compiler wrappers: mpicc, mpicxx, etc.
set(CMAKE_CXX_COMPILER mpicxx)
# Include MPI includes
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

# Include tclap includes
include_directories(SYSTEM /opt/homebrew/Cellar/tclap/1.2.5/include)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${MPI_C_LIBRARIES})

#---------
message(STATUS "${PROJECT_NAME}: done")
#set(CMAKE_CXX_STANDARD 14)

#
#include_directories(SYSTEM ${MPI_INCLUDE_PATH})
#
#add_executable(mpi-sample.cpp)

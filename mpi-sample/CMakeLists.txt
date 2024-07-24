cmake_minimum_required(VERSION 3.27)

set(EXECUTABLE_NAME "mpi-sample")
message(STATUS "${EXECUTABLE_NAME}: build starting")

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

find_package(MPI REQUIRED)

# Make sure to use the MPI compiler wrappers: mpicc, mpicxx, etc.
set(CMAKE_CXX_COMPILER mpicxx)

# Include MPI includes
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

## Include tclap includes
include_directories(SYSTEM /opt/homebrew/Cellar/tclap/1.2.5/include)

add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} ${MPI_C_LIBRARIES})

#---------
message(STATUS "${EXECUTABLE_NAME}: build done")


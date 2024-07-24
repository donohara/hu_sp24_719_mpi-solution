set(EXECUTABLE_NAME "a05_myMPI")
message(STATUS "${EXECUTABLE_NAME}: build starting")

set(SOURCES
        main.c
        MyMPI.c
        MyMPI.h)

find_package(MPI REQUIRED)
#set(CMAKE_CXX_COMPILER mpicxx)
set(CMAKE_CXX_COMPILER mpicc)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} ${MPI_C_LIBRARIES})

message(STATUS "${EXECUTABLE_NAME}: done")

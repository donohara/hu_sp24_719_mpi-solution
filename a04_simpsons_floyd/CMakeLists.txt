set(EXECUTABLE_NAME "a04_simpsons_floyd")
message(STATUS "${EXECUTABLE_NAME}: build starting")

set(SOURCES simpsons_floyd.c)

find_package(MPI REQUIRED)
# Make sure to use the MPI compiler wrappers: mpicc, mpicxx, etc.
#set(CMAKE_CXX_COMPILER mpicxx)
set(CMAKE_CXX_COMPILER mpicc)
# Include MPI includes
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} ${MPI_C_LIBRARIES})
#---------
message(STATUS "${EXECUTABLE_NAME}: build done")

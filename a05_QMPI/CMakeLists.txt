set(EXECUTABLE_NAME "a05_QMPI")
message(STATUS "${EXECUTABLE_NAME}: build starting")

set(SOURCES
        main.cpp
        QMPI.cpp
        QMPI.h
)

find_package(MPI REQUIRED)
set(CMAKE_CXX_COMPILER mpicxx)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} ${MPI_C_LIBRARIES})

message(STATUS "${EXECUTABLE_NAME}: done")

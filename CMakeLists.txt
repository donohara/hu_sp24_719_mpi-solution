cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)

#---------
set(PROJECT_NAME hu_sp24_71_mpi_solution)
message(STATUS "${PROJECT_NAME}: starting")
#---------

project(${PROJECT_NAME})


add_subdirectory(mpi-sample)
add_subdirectory(a04_simpsons_floyd)
add_subdirectory(a04_c_cpp_examples)
add_subdirectory(a05_myMPI)
add_subdirectory(a05_QMPI)


#---------
message(STATUS "${PROJECT_NAME}: done")
#---------

cmake_minimum_required(VERSION 3.27)

#---------
set(PROJECT_NAME hu_sp24_71_mpi_solution)
message(STATUS "${PROJECT_NAME}: starting")
#---------

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(mpi-sample)
add_subdirectory(a04_simpsons_floyd)
add_subdirectory(a04_c_cpp_examples)


#add_subdirectory(queue_lock_free_unbound_aba)
#add_subdirectory(queue_performance_test)
#
#add_subdirectory(list_coarse)
#add_subdirectory(list_fine)
#add_subdirectory(list_lock_free_bounded)
#add_subdirectory(list_opt)
#add_subdirectory(list_lazy)
#
#add_subdirectory(stack_lock_free_v1)
#add_subdirectory(stack_lock_free_v2)
#add_subdirectory(stack_lock_free_smart_v3)
#
#add_subdirectory(djo_stack_lock_free_bound)


#---------
message(STATUS "${PROJECT_NAME}: done")
#---------

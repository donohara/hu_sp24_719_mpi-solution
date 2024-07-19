#include <iostream>
//#include <stdio.h>
#include "mpi.h"


int main(int argc, char* argv[]) {
    std::cout << "Running example ... ";

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the total number of tasks
    int num_tasks;
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);

    // Get the task ID
    int task_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &task_id);

    std::cout << task_id << "," << num_tasks  << " Starting " << '\n';

    // Finish our MPI work
    MPI_Finalize();

    std::cout << task_id << "," << num_tasks  << " Done" << '\n';
    return 0;

}


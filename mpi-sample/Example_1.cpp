// mpi-sample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Examples.h"

int Example_1(int argc, char* argv[])
{
    int rank, size;
    char message[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr, "This program requires at least 2 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) {
        // Process 0 sends the message
        sprintf(message, "Hello, World! This is process %d.", rank);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1) {
        // Process 1 receives the message
        MPI_Recv(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received message: %s\n", message);
    }

    MPI_Finalize();
    return 0;
}

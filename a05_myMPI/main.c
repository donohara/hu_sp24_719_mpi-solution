#include <stdio.h>
//#include <stdlib.h>
//#include <string.h> /* for debugging */
#include <mpi.h>

int main(int argc, char* argv[]) {
    printf("-------Starting\n");
    int  n;
    int* local_mat;
    MPI_Comm comm;
    int p, my_rank;

    MPI_Init(&argc, &argv);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &p);
    MPI_Comm_rank(comm, &my_rank);

    printf("[%d/%d]Starting\n", my_rank, p);

    MPI_Finalize();

    printf("[%d/%d]Done\n", my_rank, p);
    return 0;
}  /* main */


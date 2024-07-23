#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for debugging */
#include <mpi.h>
#include "MyMPI.h"


// from quinn, fig 8.8, pg 188
typedef double dtype;
#define mpitype MPI_DOUBLE

int main(int argc, char* argv[]) {
    dtype **a;          // first factor, matrix
    dtype *b;           // 2nd  factor, vector
    dtype *c_block;     // partial product vector
    dtype *c;           // replicated product vector
    dtype *storage;     // matrix elements stored here
    int i, j;           // loop indices
    int id;             // process id
    int m;              // rows in matrix
    int n;              // cols in matrix
    int nprime;         // elements in vector
    int p;              // number of processes
    int rows;           // number of rows this process


    // initialize MPI, get our rank/proc-id and the number of processes
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    printf("[%d/%d]Starting\n", id, p);

    // read in the matrix
//    char *filename = malloc(strlen(argv[1]) + 1);
    char *filename = malloc(256);
    if (filename == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    char x_filename[] = "/Users/donohara/Data/50_HU/_github/hu_sp24_719_mpi_solution/a05_myMPI/adjacency_matrix_4_x_4.txt";
//    strcpy(filename, argv[1]);
    strcpy(filename, x_filename);

    printf("[%d/%d]Reading matrix file: %s\n", id, p, filename);
    read_row_striped_matrix(filename,
                            (void *) &a,
                            (void *) &storage,
                            mpitype, &m, &n, MPI_COMM_WORLD);
    rows = BLOCK_SIZE(id, p, m);
    printf("[%d/%d]rows: %d\n", id, p,rows);
    print_row_striped_matrix((void **) a, mpitype, m, n, MPI_COMM_WORLD);


    MPI_Finalize();

    printf("[%d/%d]Done\n", id, p);
    return 0;
}  /* main */


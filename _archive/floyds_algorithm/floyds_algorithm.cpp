// floyds_algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
/*
 *   Floyd's all-pairs shortest path
 *
 *   Given an NxN matrix of distances between pairs of
 *   vertices, this MPI program computes the shortest path
 *   between every pair of vertices.
 *
 *   This program shows:
 *      how to dynamically allocate multidimensional arrays
 *      how one process can handle I/O for the others
 *      broadcasting of a vector of elements
 *      messages with different tags
 *
 *   Programmed by Michael J. Quinn
 *
 *   Last modification: 4 September 2002
 */

#include <stdio.h>
#include <mpi.h>
#include "../MyMPI.h"

typedef int dtype;
#define MPI_TYPE MPI_INT

int main(int argc, char* argv[]) {
    dtype** a;         /* Doubly-subscripted array */
    dtype* storage;   /* Local portion of array elements */
    int     i, j, k;
    int     id;        /* Process rank */
    int     m;         /* Rows in matrix */
    int     n;         /* Columns in matrix */
    int     p;         /* Number of processes */
    double  time, max_time;

    void compute_shortest_paths(int, int, int**, int);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    read_row_striped_matrix(argv[1], (void*)&a,
        (void*)&storage, MPI_TYPE, &m, &n, MPI_COMM_WORLD);

    if (m != n) terminate(id, "Matrix must be square\n");

    /*
       print_row_striped_matrix ((void **) a, MPI_TYPE, m, n,
          MPI_COMM_WORLD);
    */
    MPI_Barrier(MPI_COMM_WORLD);
    time = -MPI_Wtime();
    compute_shortest_paths(id, p, (dtype**)a, n);
    time += MPI_Wtime();
    MPI_Reduce(&time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0,
        MPI_COMM_WORLD);
    if (!id) printf("Floyd, matrix size %d, %d processes: %6.2f seconds\n",
        n, p, max_time);
    /*
       print_row_striped_matrix ((void **) a, MPI_TYPE, m, n,
          MPI_COMM_WORLD);
    */
    MPI_Finalize();
}

void compute_shortest_paths(int id, int p, dtype** a, int n)
{
    int  i, j, k;
    int  offset;   /* Local index of broadcast row */
    int  root;     /* Process controlling row to be bcast */
    int* tmp;      /* Holds the broadcast row */

    tmp = (dtype*)malloc(n * sizeof(dtype));
    for (k = 0; k < n; k++) {
        root = BLOCK_OWNER(k, p, n);
        if (root == id) {
            offset = k - BLOCK_LOW(id, p, n);
            for (j = 0; j < n; j++)
                tmp[j] = a[offset][j];
        }
        MPI_Bcast(tmp, n, MPI_TYPE, root, MPI_COMM_WORLD);
        for (i = 0; i < BLOCK_SIZE(id, p, n); i++)
            for (j = 0; j < n; j++)
                a[i][j] = MIN(a[i][j], a[i][k] + tmp[j]);
    }
    free(tmp);
}

#include <iostream>
//#include <stdio.h>
#include "mpi.h"
#include "MyMPI.h"
#include "QMPI.h"

//= port from c to cpp
typedef double dtype;
#define mpitype MPI_DOUBLE


int main(int argc, char* argv[]) {

//    MPI_Datatype

    // from fig. 8.8 pg. 188
    dtype **a;
    dtype  *b;
    dtype  *c_block;
    dtype  *c;
    void  *storage;

    int i, j;
    int id;
    int m;
    int n;
    int nprime;
    int p;
    int rows;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    std::cout << id << "," << p  << " Starting " << '\n';

    char filename[] = "/Users/donohara/Data/50_HU/_github/hu_sp24_719_mpi_solution/a05_myMPI/adjacency_matrix_4_x_4.txt";
//    char *file_name; // Path to the file
    void **subs; // Uninitialized double pointer
    MPI_Datatype dtype = MPI_DOUBLE; // Type of data

// Initialize file_name, comm, dtype here...
// Subs should be a double pointer, so it should be addressed from a single pointer
    void *tempPtr = nullptr;
    subs = &tempPtr;

// Call function


//    read_row_striped_matrix(filename, &subs, &storage, dtype, &m, &n, MPI_COMM_WORLD);
//    rows = BLOCK_SIZE(id, p, m);
//    print_row_striped_matrix(subs, dtype, m, n, MPI_COMM_WORLD);

//       void **a,            /* IN - 2D array */
//   MPI_Datatype dtype,  /* IN - Matrix element type */
//   int m,               /* IN - Matrix rows */
//   int n,               /* IN - Matrix cols */
//   MPI_Comm comm)       /* IN - Communicator */

//    template<class T>
//void QMPI<T>::read_row_striped_matrix(string filename, T*** subs, T** storage, MPI_Datatype dtype,
//	int* m, int* n, MPI_Comm comm)
//    rows = BLOCK_SIZE(id, p, m)
//  not coded yet. !!
 //    void print_row_striped_matrix (

//  not coded yet. !!
//    read_replicated_vector (
//    print_replicated_vector (

//    c_block = (dtype *) malloc (rows * sizeof(dtype));
//    c = (dtype *) malloc (n * sizeof(dtype));
//
//    for (i = 0; i< rows; i++){
//        c_block[i] = 0.0;
//        for (j=0; j<n; j++){
//            c_block[i] = a[i][j] * b[j];
//        }
//    }

//    replicate_block_vector();
//    print_replicated_vector (

    // Finish our MPI work
    MPI_Finalize();

    std::cout << id << "," << p  << " Done" << '\n';
    return 0;

}


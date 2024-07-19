#pragma once
/* 
 * QMPI.h
 * Header file for a library of matrix / vector
 * input / output / redistribution functions.
 * Programmed by Michael J.Quinn
 * Last modification : 4 September 2002
 * 
 * Reworked by Kiet T. Tran,
 * Last modification: 11 July 2024
 * 
*/
#include <string>
#include <iostream>
#include <fstream>
#include <mpi.h>

using std::ifstream;
using std::string;

#define DATA_MSG		0
#define PROMPT_MSG		1
#define RESPONSE_MSG	2

#define OPEN_FILE_ERROR -1
#define MALLOC_ERROR	-2
#define TYPE_ERROR		-3

#define MIN(a,b)				((a)<(b)?(a):(b))
#define BLOCK_LOW(id,p,n)		((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n)		(BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n)		(BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER ( j ,p,n)	(((p)*((j)+1)-1)/(n))
#define PTR_SIZE				(sizeof(void*))
#define CEILING(i,j)			(((i)+(j)-1)/(j))


template<class T>
class QMPI {
public:
	QMPI();
	~QMPI();
	int get_size(MPI_Datatype t);
	T* my_malloc(int id, int bytes);
	void terminate(int id, string error_message);
	
	/* DATA DISTRIBUTION */
	void create_mixed_xfer_arrays(int id, int p, int n, int** count, int** disp);
	void create_uniform_xfer_arrays(int id, int p, int n, int** count, int** disp);
	void replicate_block_vector(T* ablock, int n, T* arep, MPI_Datatype dtype, MPI_Comm comm);

	/* INPUT */
	void read_checkerboard_matrix(string filename, T*** subs, T** storage, MPI_Datatype dtype,
		int* m, int* n, MPI_Comm grid_comm);
	void read_col_striped_matrix(string filename, T*** subs, T** storage, MPI_Datatype dtype,
		int* m, int* n, MPI_Comm comm);
	void read_row_striped_matrix(string filename, T*** subs, T** storage, MPI_Datatype dtype,
		int* m, int* n, MPI_Comm comm);
	void read_block_vector(string filename, T** v, MPI_Datatype dtype, int* n, MPI_Comm comm);
	void read_replicated_vector(string filename, T** v, MPI_Datatype dtype, int* n, MPI_Comm comm);
	
	/* OUTPUT */
	void print_submatrix(T** a, MPI_Datatype dtype, int rows, int cols);
	void print_subvector(T* a, MPI_Datatype dtype, int n);
	void print_checkerboard_matrix(T** a, MPI_Datatype dtype, int m, int n, MPI_Comm grid_comm);
	void print_col_striped_matrix(T** a, MPI_Datatype dtype, int m, int n, MPI_Comm comm);
	void print_row_striped_matrix(T** a, MPI_Datatype dtype, int m, int n, MPI_Comm comm);
	void print_block_vector(T* v, MPI_Datatype dtype, int n, MPI_Comm comm);
	void print_replicated_vector(T* v, MPI_Datatype dtype, int n, MPI_Comm comm);

private:
	std::ifstream* file = NULL;
};


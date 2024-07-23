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
#include <iostream>
#include <chrono>
#include <vector>
#include "QMPI.h"

using std::cout;
using std::endl;
using std::string;
using std::fflush;
using std::vector;

template<class T>
QMPI<T>::QMPI() {

}

template<class T>
QMPI<T>::~QMPI() {
	if (*file) {
		file->close();
		file = NULL;
	}
}

/*
 * Given MPI_Datatype 't', function 'get_size' returns the
 * size of a single datum of that data type.
*/
template<class T>
int QMPI<T>::get_size(MPI_Datatype t) {
	if (t == MPI_BYTE) return sizeof(char);
	if (t == MPI_DOUBLE) return sizeof(double);
	if (t == MPI_FLOAT) return sizeof(float);
	if (t == MPI_INT) return sizeof(int);
	cout << "Error: Unrecognized argument to 'get_size'" << endl;
    fflush(stdout);
	MPI_Abort(MPI_COMM_WORLD, TYPE_ERROR);
}

/*
 * wants to allocate some space from the heap.
 * if the memory allocation fails, the process prints an error and abort.
 */
template<class T>
T* QMPI<T>::my_malloc(int id, int bytes) {
	T* buffer;
	if ((buffer = malloc((size_t)bytes)) == NULL) {
		cout << "Error: Malloc failed for process " << id << endl;
        fflush(stdout);
		MPI_Abort(MPI_COMM_WORLD, MALLOC_ERROR);
	}
	return buffer;
}

template<class T>
void QMPI<T>::terminate(int id, string error_message) {
	if (!id) {
		cout << "Error: " << error_message << endl;
        fflush(stdout);
	}
	MPI_Finalize();
	exit(-1);
}

/*
 * creates the count and displacement arrays needed by scatter & gather
 * functions, when the number of elements send/received to/from
 * processes varies.
 */
template<class T>
void QMPI<T>::create_mixed_xfer_arrays(int id, int p, int n, int** count, int** disp) {
	*count = my_malloc(id, p * sizeof(int));
	*disp = my_malloc(id, p * sizeof(int));
	(*count)[0] = BLOCK_SIZE(0, p, n);
	(*disp)[0] = 0;

	for (int i = 1; i < p; i++) {
		(*disp)[i] = (*disp)[i - 1] + (*count)[i - 1];
		(*count)[i] = BLOCK_SIZE(i, p, n);
	}
}

/*
 * creates the count and displacement arrays needed in an all-to-all exchange, 
 * when a process gets the same number of elements from every other process.
 */
template<class T>
void QMPI<T>::create_uniform_xfer_arrays(int id, int p, int n, int** count, int** disp) {
	*count = my_malloc(id, p * sizeof(int));
	*disp = my_malloc(id, p * sizeof(int));
	(*count)[0] = BLOCK_SIZE(id, p, n);
	(*disp)[0] = 0;
	for (int i = 1; i < p; i++) {
		(*disp)[i] = (*disp)[i - 1] + (*count)[i - 1];
		(*count)[i] = BLOCK_SIZE(id, p, n);
	}
}

/*
 * is used to transform a vector from a block distribution to
 * a replicated distribution within a communicator.
 */
template<class T>
void QMPI<T>::replicate_block_vector(T* ablock, int n, T* arep, MPI_Datatype dtype, MPI_Comm comm) {
	int* cnt, * disp;
	int id, p;

	MPI_Comm_size(comm, &p);
	MPI_Comm_rank(comm, &id);
	create_mixed_xfer_arrays(id, p, n, &cnt, &disp);
	MPI_Allgatherv(ablock, cnt[id], dtype, arep, cnt, disp, dtype, comm);
	free(cnt);
	free(disp);
}

/*
 * reads a matrix from a file
 * the first two elements of the file are integers whose values are
 * the dimensions of the matrix:
 *		- m: rows
 *		- n: cols
 * what follows are m*n values representing the matrix elements 
 * stored in a row-major order.
 * this function allocates blocks of the matrix to the MPI processes
 * 
 * the number of processes must be a square number.
 * 
 */

// ----------------------------------
//  commenting out since not used in a05, and haven't resolved pointer math error
//
// ----------------------------------
//template<class T>
//void QMPI<T>::read_checkerboard_matrix(string filename, T*** subs,
//	T** storage, MPI_Datatype dtype, int* m, int* n, MPI_Comm grid_comm) {
//
//	void* buffer;
//	int  coord[2], dest_id, grid_coord[2], grid_id, grid_period[2], grid_size[2];
//	int	datum_size;  //, dest_id;
//	void* laddr, ** lptr, * raddr, * rptr;
//	int	local_cols, local_rows, p;
//	MPI_Status status;
//
//	MPI_Comm_rank(grid_comm, &grid_id);
//	MPI_Comm_size(grid_comm, &p);
//	datum_size = get_size(dtype);
//
//	/*
//	 * process 0 open files
//	 * gets number of rows(m) and number of columns (n)
//	 * broadcasts this information to the other processes.
//	 */
//
//	if (grid_id == 0) {
//		file = new std::ifstream(filename);
//		if (*file) {
//			*file >> *m;
//			*file >> *n;
//		}
//		else {
//			*m = 0;
//		}
//	}
//	MPI_Bcast(m, 1, MPI_INT, 0, grid_comm);
//	if (!(*m)) {
//		MPI_Abort(MPI_COMM_WORLD, OPEN_FILE_ERROR);
//	}
//	MPI_Bcast(n, 1, MPI_INT, 0, grid_comm);
//
//	/*
//	 * each process determines the size of the submatrix
//	 * it is responsible for.
//	 */
//	MPI_Cart_get(grid_comm, 2, grid_size, grid_period, grid_coord);
//
//	local_rows = BLOCK_SIZE(grid_coord[0], grid_size[0], *m);
//	local_cols = BLOCK_SIZE(grid_coord[1], grid_size[1], *n);
//
//	/* Dynamically allocate two-dimensional matrix `subs`*/
//	*storage = my_malloc(grid_id, local_rows * local_cols * datum_size);
//	*subs = (T**)my_malloc(grid_id, local_rows * local_cols * PTR_SIZE);
//	lptr = (T*)*subs;
//	rptr = (T*)*storage;
//	for (int i = 0; i < local_rows; i++) {
//		*(lptr++) = (T*)rptr;
////		rptr += local_rows * datum_size;
//		rptr =  (void*) ((long) local_rows * datum_size);
//	}
//
//	/*
//	 * grid process 0 reads the matrix one row at a time
//	 * and distributes each row among the MPI porcesses.
//	 */
//	if (grid_id == 0) {
//		buffer = my_malloc(grid_id, *n * datum_size);
//	}
//
//	/* for each row of pocesses in the process grid ... */
//	for (int i = 0; i < grid_size[0]; i++) {
//		coord[0] = i;
//
//		/* for each matrix row controlled by this process row ... */
//		for (int j = 0; j < BLOCK_SIZE(i, grid_size[0], *m); j++) {
//			/* Read in a row of the matrix */
//			if (grid_id == 0) {
//				vector<T> v;
//				for (int k = 0; k < *n; k++) {
//					T val;
//					*file >> val;
//					v.push_back(val);
//				}
//				copy(v.begin(), v.end(), buffer);
//			}
//
//
//			/* Distribute it among processes in the grid row ... */
//			for (int k = 0; k < grid_size[1]; k++) {
//				coord[1] = k;
//				/* Find address of first element to send */
//				raddr = buffer + BLOCK_LOW(k, grid_size[1], *n) * datum_size;
////				raddr = (void*) (((buffer + BLOCK_LOW(k, grid_size[1], *n)) * datum_size;
//
//				/* determine the grid ID of the process getting subrow */
//				MPI_Cart_rank(grid_comm, coord, &dest_id);
//
//				/* Process 0 is responsible for sending ...*/
//				if (grid_id == 0) {
//					/* it is sending (copying) to itself. */
//					if (dest_id == 0) {
//						laddr = (*subs)[j];
//						memcpy(laddr, raddr, local_cols * datum_size);
//					}
//					else { /* ssending to another process */
//						MPI_Send(raddr, BLOCK_SIZE(k, grid_size[1], *n), dtype, dest_id, 0, grid_comm);
//					}
//				}
//				else if (grid_id == dest_id) {
//					MPI_Recv((*subs[j], local_cols, dtype, 0, 0, grid_comm, &status));
//				}
//			}
//		}
//	}
//
//	if (grid_id == 0) {
//		free(buffer);
//	}
//}

/*
 * reads a matrix from a file. the first two element of the files are integers
 * whose values are the dimensions of the matrix. `m` rows, `n` columns.
 * what follows are m*n values representing the matrix elements stored in a 
 * row-major order. this function allocates blocks of columns 
 * of the matrix to the MPI processes.
 * 
 */
template<class T>
void QMPI<T>::read_col_striped_matrix(string filename, T*** subs, 
	T** storage, MPI_Datatype dtype, int* m, int* n, MPI_Comm comm) {
	
	T* buffer, * lptr, * rptr;
	int datum_size, p, id, local_cols;
	int* send_count, * send_disp;

	MPI_Comm_size(comm, &p);
	MPI_Comm_rank(comm, &id);
	datum_size = get_size(dtype);

	/* 
	 * process p-1 open file, gets number of rows and cols, 
	 * broadcasts this info to other processes.
	 */
	if (id == (p - 1)) {
		file = new std::ifstream(filename);
		if (*file) {
			*file >> *m;
			*file >> *n;
		}
		else {
			*m = 0;
		}
	}

	MPI_Bcast(m, 1, MPI_INT, p - 1, comm);
	if (!(*m)) {
		MPI_Abort(comm, OPEN_FILE_ERROR);
	}
	MPI_Bcast(n, 1, MPI_INT, p - 1, comm);
	local_cols = BLOCK_SIZE(id, p, *n);

	/* Dynamically allocate two-dimensional matrix 'subs' */
	*storage = my_malloc(id, *m * local_cols * datum_size);
	*subs = (T**)my_malloc(id, *m * PTR_SIZE);
	lptr = (T*)*subs;

	rptr = (T*)*storage;
	for (int i = 0; i < *m; i++) {
		*(lptr++) = (T*)rptr;
		rptr += local_cols * datum_size;
	}

	/* 
	 * process p-1 reads in the matrix one row at a time and 
	 * distribute each row among the MPI processes
	 */
	if (id == (p - 1)) {
		buffer = my_malloc(id, *n * datum_size);
	}
	create_mixed_xfer_arrays(id, p, *n, &send_count, &send_disp);
	for (int i = 0; i < *m; i++) {
		if (id == (p - 1)) {
			vector<T> v;
			for (int k = 0; k < *n; k++) {
				T val;
				*file >> val;
				v.push_back(val);
			}
			copy(v.begin(), v.end(), buffer);
		}
		MPI_Scatterv(buffer, send_count, send_disp, dtype,
			(*storage) + i * local_cols * datum_size, local_cols, dtype, p - 1, comm);
	}
	free(send_count);
	free(send_disp);
	if (id == (p - 1)) {
		free(buffer);
	}
}

template<class T>
void QMPI<T>::read_row_striped_matrix(string filename, T*** subs, T** storage, MPI_Datatype dtype,
	int* m, int* n, MPI_Comm comm) {
	int datum_size, id, local_rows, p, x;
	T* rptr, ** lptr;
	MPI_Status status;


	MPI_Comm_size(comm, &p);
	MPI_Comm_rank(comm, &id);
	datum_size = get_size(dtype);

	/* Process p-1 opens file, reads size of matrix,
	   and broadcasts matrix dimensions to other procs */

	if (id == (p - 1)) {
		file = new std::ifstream(filename);
		if (*file) {
			*file >> *m;
			*file >> *n;
		}
		else {
			*m = 0;
		}
	}

	MPI_Bcast(m, 1, MPI_INT, p - 1, comm);

	if (!(*m)) MPI_Abort(MPI_COMM_WORLD, OPEN_FILE_ERROR);

	MPI_Bcast(n, 1, MPI_INT, p - 1, comm);

	local_rows = BLOCK_SIZE(id, p, *m);

	/* Dynamically allocate matrix. Allow double subscripting
	 *  through 'a'. 
	 */

	*storage = (T*)my_malloc(id,	local_rows * *n * datum_size);
	*subs = (T**)my_malloc(id, local_rows * PTR_SIZE);

	lptr = (void*)&(*subs[0]);
	rptr = (void*)*storage;
	for (int i = 0; i < local_rows; i++) {
		*(lptr++) = (void*)rptr;
		rptr += *n * datum_size;
	}

	/* Process p-1 reads blocks of rows from file and
	 * sends each block to the correct destination process.
	 *  The last block it keeps. 
	 */

	if (id == (p - 1)) {
		for (int i = 0; i < p - 1; i++) {
			//x = fread(*storage, datum_size,	BLOCK_SIZE(i, p, *m) * *n, infileptr);
			MPI_Send(*storage, BLOCK_SIZE(i, p, *m) * *n, dtype, i, DATA_MSG, comm);
		}
		//x = fread(*storage, datum_size, local_rows * *n, infileptr);
		//fclose(infileptr);
	}
	else
		MPI_Recv(*storage, local_rows * *n, dtype, p - 1, DATA_MSG, comm, &status);
}
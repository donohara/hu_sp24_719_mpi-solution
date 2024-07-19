#include <iostream>
#include <stdexcept>
#include "MemoryExample.h"
#include "DistanceMatrixReader.h"
#include "DistanceMatrixWriter.h"

void memory_example() {
	std::cout << "Start memory testing ..." << std::endl;
	int m = 5, n = 3;
	MemoryExample<int>* me = new MemoryExample<int>();
	int fixed_array[3][4] = { {1,2,3,4},
                              {5,6,7,8},
                              {9,10,11,12}
                            };

	int** b = me->create2DArray(m, n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			b[i][j] =  i * n + j;
//			b[i][j] = -1; // i * n + j;
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d, ", b[i][j]);
		}
		printf("\n");
	}
	me->destroy2DArray(b);
	delete me;
	std::cout << "Done memory testing ..." << std::endl;
}

/*
* 1. compute number of rows per process.
* 2. create an array that has `numProcesses` entries.
* 3. assign each entry a `numRow` value. 
* 4. if remainer is not zero, add 1 to the first `rem` processes.
* 
* The first process always has the appropriate number of rows (even if the remainder exists).
* Use this knowledge to create the storage needed for the reading operations.
*/
int* makeNumRowsByProcess(int totalRows, int numProcesses) {
	int numRows = totalRows / numProcesses;
	int* numRowsByProcess = new int[numProcesses];
	int rem = totalRows % numProcesses;
	for (int p = 0; p < numProcesses; p++) {
		if (rem > 0) {
			numRowsByProcess[p] = numRows + 1;
			rem--;
		}
		else {
			numRowsByProcess[p] = numRows;
		}
	}
	return numRowsByProcess;
};


void distance_matrix_test_int(const std::string infilename, const std::string outfilename, 
							  int totalRows, int numCols, int numProcesses) {
	std::cout << "Start distance_matrix_test_int ... \n";
	std::cout << "...infilename: " << infilename << std::endl;
	std::cout << "...outfilename: " << outfilename << std::endl;
	std::cout << "...totalRows: " << totalRows << ", numCols: " << numCols << ", numProcesses: " << numProcesses << std::endl;

    std::cout << "makeNumRowsByProcess ... \n";
	int* numRowsByProcess = makeNumRowsByProcess(totalRows, numProcesses);

    std::cout << "create2DArray ... \n";
	MemoryExample<int>* me = new MemoryExample<int>();
	int** storage = me->create2DArray(numRowsByProcess[0], numCols);;

    std::cout << "Open files ... \n";
	DistanceMatrixReader<int> dmr(infilename);
	DistanceMatrixWriter<int> dmw(outfilename);

    std::cout << "Read and write data ... \n";
	for (int p = 0; p < numProcesses; p++) {
		dmr.readRows(storage, numRowsByProcess[p], numCols);
        // -- print the rows
		for (int row = 0; row < numRowsByProcess[p]; row++) {
			for (int col = 0; col < numCols; col++) {
				std::cout << storage[row][col] << " ";
			}
			std::cout << std::endl;
		}
		// testing writer-- change the data
        for (int row = 0; row < numRowsByProcess[p]; row++) {
            for (int col = 0; col < numCols; col++) {
                storage[row][col] *= 100;
            }
        }
		dmw.writeRows(storage, numRowsByProcess[p], numCols);
	}

    std::cout << "Free resources ... \n";
	me->destroy2DArray(storage);
	delete me;

	std::cout << "Done testing distance matrix reader ..." << std::endl;
	std::cout << std::flush;
}

void distance_matrix_test_float(const std::string infilename, const std::string outfilename,
	int totalRows, int numCols, int numProcesses) {
//	std::cout << "Start testing distance matrix reader ... " << infilename << std::endl;
//	std::cout << "Start testing distance matrix writer ... " << outfilename << std::endl;

    std::cout << "Start distance_matrix_test_float ... \n";
    std::cout << "...infilename: " << infilename << std::endl;
    std::cout << "...outfilename: " << outfilename << std::endl;
    std::cout << "...totalRows: " << totalRows << ", numCols: " << numCols << ", numProcesses: " << numProcesses << std::endl;

    std::cout << "makeNumRowsByProcess ... \n";
	int* numRowsByProcess = makeNumRowsByProcess(totalRows, numProcesses);

    std::cout << "create2DArray ... \n";
	MemoryExample<float>* me = new MemoryExample<float>();
	float** storage = me->create2DArray(numRowsByProcess[0], numCols);;

    std::cout << "Open files ... \n";
	DistanceMatrixReader<float> dmr(infilename);
	DistanceMatrixWriter<float> dmw(outfilename);

    std::cout << "Read and write data ... \n";
	for (int p = 0; p < numProcesses; p++) {
		dmr.readRows(storage, numRowsByProcess[p], numCols);
        // -- print the rows
		for (int row = 0; row < numRowsByProcess[p]; row++) {
			for (int col = 0; col < numCols; col++) {
//				storage[row][col] += 1.0;
				std::cout << storage[row][col] << " ";
			}
			std::cout << std::endl;
		}
        // testing writer-- change the data
        for (int row = 0; row < numRowsByProcess[p]; row++) {
            for (int col = 0; col < numCols; col++) {
				storage[row][col] *= 100.0;
            }
        }
		dmw.writeRows(storage, numRowsByProcess[p], numCols);
	}

    std::cout << "Free resources ... \n";
	me->destroy2DArray(storage);
	delete me;

	std::cout << "Done testing distance matrix reader ..." << std::endl;
	std::cout << std::flush;
}

int main()
{
    std::cout << "Starting\n";

	memory_example();

    std::string filename_in = "/Users/donohara/Data/50_HU/_github/hu_sp24_719_mpi_solution/a04_c_cpp_examples/adjacency_matrix_01_4x4_int.txt";
    std::string filename_out = "/Users/donohara/Data/50_HU/_github/hu_sp24_719_mpi_solution/a04_c_cpp_examples/test_data_out_int.txt";
	distance_matrix_test_int(filename_in, filename_out, 4, 4, 1);

    filename_in = "/Users/donohara/Data/50_HU/_github/hu_sp24_719_mpi_solution/a04_c_cpp_examples/adjacency_matrix_01_4x4_float.txt";
    filename_out = "/Users/donohara/Data/50_HU/_github/hu_sp24_719_mpi_solution/a04_c_cpp_examples/test_data_out_float.txt";
    distance_matrix_test_float(filename_in, filename_out, 4, 4, 1);

    std::cout << "Done\n";
};


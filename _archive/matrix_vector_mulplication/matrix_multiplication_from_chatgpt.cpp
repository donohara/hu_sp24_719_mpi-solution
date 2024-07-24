//#include <iostream>
//#include <vector>
//#include <mpi.h>
//
//using namespace std;
//
//// Function to print matrix
//void printMatrix(const vector<vector<int>>& matrix) {
//    for (const auto& row : matrix) {
//        for (int value : row) {
//            cout << value << "\t";
//        }
//        cout << endl;
//    }
//}
//
//// Function to perform matrix multiplication
//vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
//    int m = A.size();
//    int n = B[0].size();
//    int p = B.size();
//
//    // Resultant matrix initialized with zeros
//    vector<vector<int>> result(m, vector<int>(n, 0));
//
//    for (int i = 0; i < m; ++i) {
//        for (int j = 0; j < n; ++j) {
//            for (int k = 0; k < p; ++k) {
//                result[i][j] += A[i][k] * B[k][j];
//            }
//        }
//    }
//
//    return result;
//}
//
//int main(int argc, char** argv) {
//    // Initialize MPI
//    MPI_Init(&argc, &argv);
//
//    int rank, size;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    // Example matrices
//    vector<vector<int>> A = { {1, 2, 3},
//                              {4, 5, 6} };
//
//    vector<vector<int>> B = { {7, 8},
//                              {9, 10},
//                              {11, 12} };
//
//    // Divide the work among MPI processes
//    vector<vector<int>> localA(A.size() / size, vector<int>(A[0].size()));
//    vector<vector<int>> localResult(A.size() / size, vector<int>(B[0].size()));
//    MPI_Scatter(A.data(), A.size() / size * A[0].size(), MPI_INT, localA.data(), A.size() / size * A[0].size(), MPI_INT, 0, MPI_COMM_WORLD);
//
//    // Perform local matrix multiplication
//    vector<vector<int>> localB(B.size(), vector<int>(B[0].size()));
//    MPI_Bcast(B.data(), B.size() * B[0].size(), MPI_INT, 0, MPI_COMM_WORLD);
//    MPI_Barrier(MPI_COMM_WORLD);
//
//    for (int i = 0; i < B.size(); ++i) {
//        for (int j = 0; j < B[0].size(); ++j) {
//            localB[i][j] = B[i][j];
//        }
//    }
//
//    localResult = multiplyMatrices(localA, localB);
//
//    // Gather the results
//    vector<vector<int>> result(A.size(), vector<int>(B[0].size()));
//    MPI_Gather(localResult.data(), localResult.size() * localResult[0].size(), MPI_INT, result.data(), localResult.size() * localResult[0].size(), MPI_INT, 0, MPI_COMM_WORLD);
//
//    // Print the result from process 0
//    if (rank == 0) {
//        cout << "Resultant matrix:" << endl;
//        printMatrix(result);
//    }
//
//    // Finalize MPI
//    MPI_Finalize();
//
//    return 0;
//}

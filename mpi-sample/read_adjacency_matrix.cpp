/**
* This code is from a question to ChatGPT ...
*
* "c++ example of reading adjacency matrix from a file"
*
*/
#include <iostream>
#include <fstream>
#include <vector>
#include "Examples.h"

// Function to read an adjacency matrix from a file
std::vector<std::vector<int>> readAdjacencyMatrixFromFile(const std::string filename) {

    std::cout << "readAdjancyMatrixFromFile function ..." << std::endl;

    std::ifstream infile(filename);
    std::vector<std::vector<int>> adjacencyMatrix;

    if (!infile.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return adjacencyMatrix; // Return an empty matrix on error
    }

    int numVertices;
    infile >> numVertices; // Assuming the first number in the file represents the number of vertices
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices));

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            infile >> adjacencyMatrix[i][j]; // Read each element from the file
            std::cout << adjacencyMatrix[i][j] << std::endl;
        }
    }

    infile.close();
    return adjacencyMatrix;
}

//int example_read_adjacency_matrix_from_a_file(const std::string& fileName) {
int example_read_adjacency_matrix_from_a_file() {
    std::string fileName = "/Users/donohara/Data/50_HU/_github/hu_sp24_719_mpi_solution/mpi-sample/adjacency_matrix_01_4x4_int.txt";

    std::cout << "example_read_adjacency_matrix_from_a_file function ..." << std::endl;
    std::cout << "file name: " << fileName << std::endl;
    std::vector<std::vector<int>> adjacencyMatrix = readAdjacencyMatrixFromFile(fileName);

    // Display the adjacency matrix
    std::cout << "Adjacency Matrix:" << std::endl;
    for (const auto& row : adjacencyMatrix) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

/**
* This code is from a question to ChatGPT ...
*
* "c++ example of reading adjacency matrix from a file"
*
*/
#include <iostream>
#include <fstream>
#include <vector>

// Function to read an adjacency matrix from a file
std::vector<std::vector<int>> readAdjacencyMatrixFromFile(const std::string filename) {

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
        }
    }

    infile.close();
    return adjacencyMatrix;
}

int example_reading_adjacency_matrix_from_a_file(const std::string& fileName) {
    std::cout << "readAdjancyMatrixFromFile function ..." << std::endl;
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

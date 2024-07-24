/*
* Code gemerated from ChatGPT for this question: 
* Read a matrix from a file.
* 
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Function to read matrix from file
vector<vector<int>> readMatrixFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> matrix;
    if (file.is_open()) {
        int rows, cols;
        file >> rows >> cols; // Assuming the first line of the file contains number of rows and columns
        matrix.resize(rows, vector<int>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file >> matrix[i][j];
            }
        }
        file.close();
    }
    else {
        cerr << "Unable to open file " << filename << endl;
    }
    return matrix;
}

// Function to print matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

//int main(int argc, char* argv[]) {
//    string filename = "matrix.txt"; // Change this to the name of your file
//    filename = argv[1];
//    vector<vector<int>> matrix = readMatrixFromFile(filename);
//    cout << "Matrix read from file:" << endl;
//    printMatrix(matrix);
//    return 0;
//}

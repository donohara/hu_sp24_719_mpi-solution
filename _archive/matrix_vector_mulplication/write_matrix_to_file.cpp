/*
* From ChatGPT after asking, 'writing a matrix to a file'
* 
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Function to write matrix to file
void writeMatrixToFile(const vector<vector<int>>& matrix, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        file << rows << " " << cols << endl; // Writing number of rows and columns as the first line
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file << matrix[i][j] << " ";
            }
            file << endl;
        }
        file.close();
        cout << "Matrix successfully written to file: " << filename << endl;
    }
    else {
        cerr << "Unable to open file " << filename << " for writing." << endl;
    }
}
//
//int main() {
//    vector<vector<int>> matrix = {
//        {1, 2, 3},
//        {4, 5, 6},
//        {7, 8, 9}
//    };
//
//    string filename = "output_matrix.txt"; // Change this to the desired output file name
//    writeMatrixToFile(matrix, filename);
//
//    return 0;
//}

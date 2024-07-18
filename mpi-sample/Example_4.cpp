// Serial gaussian elimination
// By: Nick from CoffeeBeforeArch

#include "Examples.h"

// Helper function to print the matrix
void print_matrix(const float* matrix, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            std::cout << matrix[i * dim + j] << ' ';
        }
        std::cout << '\n';
    }
}

int Example_4() {
    std::cout << "Example_4 starting" << '\n';
    // Create a random number generator
    std::mt19937 mt(123);
    std::uniform_real_distribution dist(1.0f, 2.0f);

    // Create a matrix
    std::vector<float> m;
//    const int dim = 1 << 12;
    const int dim = 1 << 2;
    std::generate_n(std::back_inserter(m), dim * dim, [&] { return dist(mt); });

    // Performance gaussian elimination
    for (int row = 0; row < dim; row++) {
        // Get the value of the pivot
        auto pivot = m[row * dim + row];

        // Divide the rest of the row by the pivot
        for (int col = row; col < dim; col++) {
            m[row * dim + col] /= pivot;
        }

        // Eliminate the pivot col from the remaining rows
        for (int elim_row = row + 1; elim_row < dim; elim_row++) {
            // Get the scaling factor for elimination
            auto scale = m[elim_row * dim + row];

            // Remove the pivot
            for (int col = row; col < dim; col++) {
                m[elim_row * dim + col] -= m[row * dim + col] * scale;
            }
        }
    }
//    print_matrix(m, dim);
    std::cout << "Example_4 done" << '\n';
    return 0;
}
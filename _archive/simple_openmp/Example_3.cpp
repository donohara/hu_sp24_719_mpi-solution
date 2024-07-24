// An example using OpenMP
// By: Nick from CoffeeBeforeArch

#include "Examples.h"

void Example_3() {
    // Create a random number generator
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution dist(0.0f, 1.0f);

    // Create vectors of random numbers
    const int num_elements = 1 << 24;
    std::vector<float> v_in;
    std::generate_n(std::back_inserter(v_in), num_elements,
        [&] { return dist(mt); });

    // Output vector is just 0s
    std::vector<float> v_out(num_elements);

#pragma omp parallel for
    for (int i = 0; i < num_elements; i++) {
        // Square v_in and set v_out
        v_out[i] = v_in[i] * v_in[i];
    }
}

// MPI parallel gaussian elimination
// By: Nick from CoffeeBeforeArch

#include "Examples.h"


int Example_5(int argc, char* argv[]) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the total number of tasks
    int num_tasks;
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);

    // Calculate the number of rows mapped to each process
    // Assumes this divides evenly
//    const int dim = 1 << 12;
    const int dim = 1 << 3;
    const int n_rows = dim / num_tasks;

    // Get the task ID
    int task_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &task_id);
    const int start_row = task_id * n_rows;
    const int end_row = start_row + n_rows;

    std::cout << task_id << "," << num_tasks  << " Starting " << '\n';

    // Matrix - Only initialized in rank 0
    std::unique_ptr<float[]> matrix;

    // Each process will store a chunk of the matrix
    auto m_chunk = std::make_unique<float[]>(dim * n_rows);

    // Each process will receive a pivot row each iteration
    auto pivot_row = std::make_unique<float[]>(dim);

    // Only rank 0 create/initializes the matrix
    if (task_id == 0) {
        std::cout << task_id << "," << num_tasks  << " Init matrix " << '\n';
        // Create a random number generator
        std::mt19937 mt(123);
        std::uniform_real_distribution dist(1.0f, 2.0f);

        // Create a matrix
        matrix = std::make_unique<float[]>(dim * dim);
        std::generate(matrix.get(), matrix.get() + dim * dim,
            [&] { return dist(mt); });
    }

    // Before doing anything, send parts of the matrix to each process
    std::cout << task_id << "," << num_tasks  << " MPI_Scatter " << '\n';

    MPI_Scatter(matrix.get(), dim * n_rows, MPI_FLOAT, m_chunk.get(),
        dim * n_rows, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Store requests that for non-blocking sends
    std::vector<MPI_Request> requests(num_tasks);

    // Performance gaussian elimination
    std::cout << task_id << "," << num_tasks  << " send/wait/recv " << '\n';
    for (int row = 0; row < end_row; row++) {
        // See if this process is responsible for the pivot calculation
        auto mapped_rank = row / n_rows;

        // If the row is mapped to this rank...
        if (task_id == mapped_rank) {
            // Calculate the row in the local matrix
            auto local_row = row % n_rows;

            // Get the value of the pivot
            auto pivot = m_chunk[local_row * dim + row];

            // Divide the rest of the row by the pivot
            for (int col = row; col < dim; col++) {
                m_chunk[local_row * dim + col] /= pivot;
            }

            // Send the pivot row to the other processes
            for (int i = mapped_rank + 1; i < num_tasks; i++) {
                MPI_Isend(m_chunk.get() + dim * local_row, dim, MPI_FLOAT, i, 0,
                    MPI_COMM_WORLD, &requests[i]);
            }

            // Eliminate the for the local rows
            for (int elim_row = local_row + 1; elim_row < n_rows; elim_row++) {
                // Get the scaling factor for elimination
                auto scale = m_chunk[elim_row * dim + row];

                // Remove the pivot
                for (int col = row; col < dim; col++) {
                    m_chunk[elim_row * dim + col] -=
                        m_chunk[local_row * dim + col] * scale;
                }
            }

            // Check if there are any outstanding messages
            for (int i = mapped_rank + 1; i < num_tasks; i++) {
                MPI_Wait(&requests[i], MPI_STATUS_IGNORE);
            }
        }
        else {
            // Receive pivot row
            MPI_Recv(pivot_row.get(), dim, MPI_FLOAT, mapped_rank, 0, MPI_COMM_WORLD,
                MPI_STATUS_IGNORE);

            // Skip rows that have been fully processed
            for (int elim_row = 0; elim_row < n_rows; elim_row++) {
                // Get the scaling factor for elimination
                auto scale = m_chunk[elim_row * dim + row];

                // Remove the pivot
                for (int col = row; col < dim; col++) {
                    m_chunk[elim_row * dim + col] -= pivot_row[col] * scale;
                }
            }
        }
    }

    // Gather the final results into rank 0
    std::cout << task_id << "," << num_tasks  << " MPI_Gather " << '\n';

    MPI_Gather(m_chunk.get(), n_rows * dim, MPI_FLOAT, matrix.get(), n_rows * dim,
        MPI_FLOAT, 0, MPI_COMM_WORLD);
//    std::cout << task_id << "," << num_tasks  << " result " << '\n';

    // Finish our MPI work
    MPI_Finalize();

    std::cout << task_id << "," << num_tasks  << " Done" << '\n';
    return 0;
}
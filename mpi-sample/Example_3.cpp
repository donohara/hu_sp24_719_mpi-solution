// An example of sum reduction using MPI
// By: Nick from CoffeeBeforeArch

#include "Examples.h"
#include <numeric>



int Example_3(int argc, char* argv[]) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the total number of tasks
    int num_tasks;
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);

    // Calculate chunk size
    // Assume this divides evenly
    const int num_elements = 1 << 10;
    const int chunk_size = num_elements / num_tasks;

    // Get the task ID
    int task_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &task_id);

    std::cout << task_id << "," << num_tasks  << " Starting " << '\n';

    // Create buffer for send (only initialized in rank 0)
    std::unique_ptr<int[]> send_ptr;

    // Generate random numbers from rank 0
    if (task_id == 0) {
        // Allocate memory for send buffer
        send_ptr = std::make_unique<int[]>(num_elements);

        // Create random number generator
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(1, 1);

        // Create random data
        std::generate(send_ptr.get(), send_ptr.get() + num_elements,
            [&] { return dist(mt); });
        std::cout << task_id << "," << num_tasks  << " generated " << num_elements << " items \n";
    }

    // Receive buffer
    auto recv_buffer = std::make_unique<int[]>(chunk_size);

    // Perform the scatter of the data to different threads
    std::cout << task_id << "," << num_tasks  << " MPI_Scatter " << '\n';
    MPI_Scatter(send_ptr.get(), chunk_size, MPI_INT, recv_buffer.get(),
        chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate partial results in each thread
    auto local_result =
        std::reduce(recv_buffer.get(), recv_buffer.get() + chunk_size);
    

    // Perform the reduction
    // why 2x ??
    int global_result = 0;
    std::cout << task_id << "," << num_tasks  << " MPI_Reduce-1 " << '\n';
    MPI_Reduce(&local_result, &global_result, 1, MPI_INT, MPI_SUM, 0,
        MPI_COMM_WORLD);

    std::cout << task_id << "," << num_tasks  << " MPI_Reduce-2 " << '\n';
    MPI_Reduce(&local_result, &global_result, 1, MPI_INT, MPI_SUM, 0,
        MPI_COMM_WORLD);

    // Print the result from rank 0
    if (task_id == 0) {
        std::cout << task_id << "," << num_tasks  << " result " << global_result << '\n';
        std::cout << '\n';
    }

    // Finish our MPI work
    MPI_Finalize();
    std::cout << task_id << "," << num_tasks  << " Done " << '\n';
    return 0;
}
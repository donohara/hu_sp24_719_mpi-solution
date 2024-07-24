// cpp_compiler_options_openmp.cpp
#include "Examples.h"

volatile DWORD dwStart;
volatile int global;



int main(int argc, char* argv[]) {

    if (argc < 2)
    {
        printf("Must provide the example number!\n");
        return -1;
    }

    int steps = 1000000000;
    std::chrono::steady_clock::time_point begin;
    begin = StartTimer();
    dwStart = GetTickCount();
    double d;

    int example_no = atoi(argv[1]);
    switch (example_no)
    {
    case 1:
        d = Example_1(steps);
        std::cout << "Example_1: For " << steps << " steps, pi = " << d << ", " 
            << GetDurationInMicroSeconds(begin, StopTimer()) << " microseconds" << std::endl;
        break;
    case 2:
        d = Example_2(steps);
        std::cout << "Example_2: For " << steps << " steps, pi = " << d << ", " 
            << GetDurationInMicroSeconds(begin, StopTimer()) << " microseconds" << std::endl;
        break;
    
    case 3:
        Example_3();
        std::cout << "Example_3: completes in " << GetDurationInMicroSeconds(begin, StopTimer()) << " microseconds" << std::endl;
        break;
    default:
        printf("Invalid example number %d\n", example_no);
        return -2;
    }

    return 0;
}
// cpp_compiler_options_openmp.cpp
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "common.h"

volatile DWORD dwStart;
volatile int global = 0;

double test1(int num_steps) {
    int i;
    global++;
    double x, pi, sum = 0.0, step;

    step = 1.0 / (double)num_steps;

    for (i = 1; i <= num_steps; i++) {
        x = (i - 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    return pi;
}

double test2(int num_steps) {
    int i;
    global++;
    double x, pi, sum = 0.0, step;

    step = 1.0 / (double)num_steps;

#pragma omp parallel for reduction(+:sum) private(x)
    for (i = 1; i <= num_steps; i++) {
        x = (i - 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    return pi;
}

int main(int argc, char* argv[]) {
    double   d;
    int n = 1000000000;

    if (argc > 1)
        n = atoi(argv[1]);

    std::chrono::steady_clock::time_point begin;
    begin = StartTimer();
    dwStart = GetTickCount();
    d = test1(n);
    std::cout << "test1(): For " << n << " steps, pi = " << d << ", " << GetDurationInMicroSeconds(begin, StopTimer()) << " microseconds" << std::endl;
    printf_s("For %d steps, pi = %.15f, %d milliseconds\n", n, d, GetTickCount() - dwStart);

    dwStart = GetTickCount();
    begin = StartTimer();
    d = test2(n);
    std::cout << "test2(): For " << n << " steps, pi = " << d << ", " << GetDurationInMicroSeconds(begin, StopTimer()) << " microseconds" << std::endl;
    printf_s("For %d steps, pi = %.15f, %d milliseconds\n", n, d, GetTickCount() - dwStart);
}
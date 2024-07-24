#include "Examples.h"

extern volatile DWORD dwStart;
extern volatile int global;


double Example_1(int num_steps) {
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
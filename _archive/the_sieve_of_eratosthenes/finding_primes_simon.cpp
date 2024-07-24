// the_sieve_of_eratosthenes.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
    Create a list of natural numbers 2, 3, 4, ..., n, none of which is marked.
    2. Set k to 2, the first unmarked number on the list.
    3. Repeat
        (a) Mark all multiples of k between k2 and n
        (b) Find the smallest number greater thank that is unmarked.Set k to this new value.
    Until k2 > 11
    4. The unmarked numbers are primes.
    
*/

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

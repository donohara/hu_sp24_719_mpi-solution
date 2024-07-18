// mpi-sample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include "mpi.h"
#include "Examples.h"
#include <tclap/CmdLine.h>

extern int example_no  = 1;
extern std::string fileName = "";

static int get_example_parameters(int argc, char** argv) {
    TCLAP::CmdLine cmd("Getting example number", ' ', "1.0");

    TCLAP::ValueArg<int> eArg("e", "example_no", "Example number to run", true, 1, "int");
    cmd.add(eArg);

    TCLAP::ValueArg<std::string> fArg("f", "fileName", "Name of adjacency matrix", false, "", "string");
    cmd.add(fArg);

    cmd.parse(argc, argv);
    example_no = eArg.getValue();
    fileName = fArg.getValue();
    return 0;
}

int main(int argc, char* argv[]) {
    std::cout << "Running example ... ";
    get_example_parameters(argc, argv);

    std::cout << " ex number: " << example_no << std::endl;
    std::cout << " filename: " <<fileName << std::endl;
//    return -1;

    std::string& fileName2 = fileName;
    fileName2 = "/Users/donohara/Data/50_HU/_github/hu_sp24_719_mpi_solution/mpi-sample/sample_adjacency_matrix.txt";

    switch (example_no)
    {
    case 0: 
        return Example_0(argc, argv);
    case 1:
        return Example_1(argc, argv);
    case 2:
        return Example_2(argc, argv);
    case 3:
        return Example_3(argc, argv);
    case 4:
        return Example_4(); 
    case 5:
        return Example_5(argc, argv);
//    case 6:
//        return The_Sieve_of_Eratosthenes(argc, argv);
    case 7: {

        return floyds_algorithm(argc, argv, const_cast<char*>(fileName2.c_str()));
    }
    case 8:
        return example_read_adjacency_matrix_from_a_file();
    default:
        printf("Invalid example number %d\n", example_no);
        return -2;
    }
    return Example_1(argc, argv);
}

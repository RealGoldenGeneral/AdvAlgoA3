/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#include <iostream>
#include <cstdlib>
#include "tests/MergeSortTests.h"
#include "tests/RadixSortTests.h"
#include "tests/LibraryRestructuringTests.h"
#include "include/LExceptions.h"
/*
 * This is the driver file which directs the project on testing different modules.
 * For each new testing function add a new case with the next available "module_choice" to be able to test it out.
 */

int main(int argc, char* argv[]) {
    int module_choice = 0;

    if (argc > 1) {
        module_choice = atoi(argv[1]);
    }
    switch (module_choice) {
        case 0: // Testing Assignment 2:
            std::cout << ">> MergeSort:\t\t\t\t\t\t";
            mergeSortTests();
            std::cout << ">> RadixSort:\t\t\t\t\t\t";
            radixSortTests();
            std::cout << ">> Library Restructuring System: \t";
            libraryRestructuringTests();
            break;
        default:
            throw std::invalid_argument("Invalid module choice");
            break;
    }
    return 0;
}

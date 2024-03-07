cmake_minimum_required(VERSION 3.25)
project(8042_Assignment_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(8042_Assignment_3
        include/Date.h
        include/Utils.h
        include/UnorderedSet.h
        include/HashTable.h
        include/RadixSort.h
        include/MergeSort.h
        src/LibraryRestructuring.cpp
        tests/TestEnvironment.h
        tests/LibraryRestructuringTests.h
        main.cpp)

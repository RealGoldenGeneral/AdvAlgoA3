/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef RADIXSORT_H
#define RADIXSORT_H
/**
 * Implementation the radix sort algorithm.
 */
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>

template <typename T>
class RadixSort {
public:
    RadixSort(std::vector<T>& elements, std::function<int(const T&)> getKeyFunction)
            : elements_(elements), getKeyFunction_(getKeyFunction) {}

    // TODO implement the following functions in ../src/RadixSort.cpp
    // Inline sorting method
    void sort();

private:
    std::vector<T>& elements_;
    std::function<int(const T&)> getKeyFunction_;
    // TODO implement the following functions in ../src/RadixSort.cpp
    int getMaxDigitCount();
    int getDigitCount(int number);
    void countingSort(int digit);
    int getDigitValue(int number, int digit);
};

#include "../src/RadixSort.cpp"

#endif //RADIXSORT_H


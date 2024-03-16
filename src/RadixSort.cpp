//
// Created by goldengeneral on 16/03/24.
//

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include "../include/RadixSort.h"


template <typename T>
int RadixSort<T>::getDigitCount(int number) {
    if (number == 0) {
        return 1;
    }

    return static_cast<int>(floor(log10(abs(number))) + 1);
}

template <typename T>
int RadixSort<T>::getMaxDigitCount() {
    int maxDigitCount = 0;

    for (const T& element : elements_) {
        int digitCount = getDigitCount(getKeyFunction_(element));
        if (digitCount > maxDigitCount) {
            maxDigitCount = digitCount;
        }
    }

    return maxDigitCount;
}

template <typename T>
int RadixSort<T>::getDigitValue(int number, int digit) {
    return (number / static_cast<int>(pow(10, digit))) % 10;
}

template <typename T>
void RadixSort<T>::countingSort(int digit) {
    int n = elements_.size();

    // Find maximum element to determine  range of counting array
    int maxDigitValue = 9;

    // Initialize count array with zeros
    std::vector<int> count(maxDigitValue + 1, 0);

    // Store number of occurrences of each digit value to position
    for (const T& element : elements_) {
        int key = getDigitValue(getKeyFunction_(element), digit);
        count[key]++;
    }

    // Modify count array such that each element stores sum of previous counts
    for (int i = 1; i <= maxDigitValue; ++i) {
        count[i] += count[i - 1];
    }

    // Create temporary vector to store sorted elements
    std::vector<T> sorted(n);

    // Build sorted array
    for (int i = n - 1; i >= 0; --i) {
        int key = getDigitValue(getKeyFunction_(elements_[i]), digit);
        sorted[count[key] - 1] = elements_[i];
        count[key]--;
    }

    // Copy sorted elements back to the original vector
    for (int i = 0; i < n; ++i) {
        elements_[i] = sorted[i];
    }
}

template <typename T>
void RadixSort<T>::sort() {
    // Get maximum number of digits
    int maxDigitCount = getMaxDigitCount();

    // Perform counting sort for each digit position, starting from least significant digit
    for (int digit = 0; digit < maxDigitCount; ++digit) {
        countingSort(digit);
    }
}
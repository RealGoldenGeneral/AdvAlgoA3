//
// Created by 1970n on 2024-03-07.
//

#include <vector>
#include <functional>
#include "../include/MergeSort.h"

template <typename T>
void MergeSort<T>::merge(std::vector<T> &arr, const std::vector<T> &left, const std::vector<T> &right) {
    int leftPos = 0;
    int rightPos = 0;
    int arrayPos = 0;
    while (leftPos < left.size() && rightPos < right.size()) {
        if (compare(left[leftPos], right[rightPos])) {
            arr[arrayPos++] = left[leftPos++];
        } else {
            arr[arrayPos++] = right[rightPos++];
        }
    }

    while (leftPos < left.size()) {
        arr[arrayPos++] = left[leftPos++];
    }

    while (rightPos < right.size()) {
        arr[arrayPos++] = right[rightPos++];
    }
}

template <typename T>
void MergeSort<T>::sort(std::vector<T> &arr) {
    int center = (0 + (arr.size() - 1)) / 2;
    if (0 < arr.size() - 1) {
        typename std::vector<T>::const_iterator begin = arr.begin();
        typename std::vector<T>::const_iterator itCenter = arr.begin() + center;
        typename std::vector<T>::const_iterator end = arr.begin() + arr.size();
        std::vector<T> left = std::vector<T>(begin, itCenter + 1);
        std::vector<T> right = std::vector<T>(itCenter + 1, end);
        sort(left);
        sort(right);
        merge(arr, left, right);
    }
}
//
// Created by 1970n on 2024-03-07.
//

#include <vector>
#include <functional>
#include "../include/MergeSort.h"

template <typename T>
void MergeSort<T>::merge(std::vector<T> &arr, const std::vector<T> &left, const std::vector<T> &right) {
}

template <typename T>
void MergeSort<T>::sort(std::vector<T> &arr) {
    int center = (0 + (arr.size() - 1)) / 2;
    if (0 < arr.size() - 1) {
        auto itCenter = arr.begin() + center;
        sort(std::vector<T>(arr.begin(), itCenter));
        sort(std::vector<T>(itCenter + 1, arr.end()));
        merge(arr, std::vector<T>(arr.begin(), itCenter), std::vector<T>(itCenter + 1, arr.end()));
    }
}
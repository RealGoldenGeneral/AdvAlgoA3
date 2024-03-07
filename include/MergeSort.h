/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef MERGESORT_H
#define MERGESORT_H
/**
 * Implementation the merge sort algorithm.
 */
#include <vector>
#include <functional>

template <typename T>
class MergeSort {
public:
    explicit MergeSort(std::function<bool(const T&, const T&)> compareFunc) : compare(compareFunc) {}
    // TODO implement the following functions in ../src/MergeSort.cpp
    void sort(std::vector<T>& arr);

private:
    std::function<bool(const T&, const T&)> compare;
    void merge(std::vector<T>& arr, const std::vector<T>& left, const std::vector<T>& right);
};

#include "../src/MergeSort.cpp"

#endif //MERGESORT_H

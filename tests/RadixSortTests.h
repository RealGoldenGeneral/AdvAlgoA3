/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef RADIXSORTTESTS_H
#define RADIXSORTTESTS_H
#include <iostream>
#include <cmath>
#include "../include/Utils.h"
#include "../include/RadixSort.h"
#include "TestEnvironment.h"

int intKey(const int& num) {
    return num;
}

int doubleKey(const double& num) {
    return static_cast<int>(num * 100);
}

std::pair<int, int> radixSortNumberVector(){
    int passedTests = 0;
    TestEnvironment env;
    std::vector<int> intVec = {170, 45, 75, 90, 802, 24, 2, 66};
    RadixSort<int> radixSort(intVec, [](const int& num) { return num; });
    radixSort.sort();
    passedTests += a_assert(intVec[0] == 2);
    passedTests += a_assert(intVec[1] == 24);
    passedTests += a_assert(intVec[2] == 45);
    passedTests += a_assert(intVec[3] == 66);
    passedTests += a_assert(intVec[4] == 75);
    passedTests += a_assert(intVec[5] == 90);
    passedTests += a_assert(intVec[6] == 170);
    passedTests += a_assert(intVec[7] == 802);
    std::vector<int> intVector = {43, 12, 7, 65, 23, 9};
    RadixSort<int> intSort(intVector, intKey);
    intSort.sort();
    passedTests += a_assert(intVector == std::vector<int>({7, 9, 12, 23, 43, 65}));
    std::vector<double> doubleVector = {3.14, 1.618, 2.718, 0.577};
    RadixSort<double> doubleSort(doubleVector, doubleKey);
    doubleSort.sort();
    passedTests += a_assert(doubleVector == std::vector<double>({0.577, 1.618, 2.718, 3.14}));
    std::vector<int> largeIntVector;
    for (int i = 100000; i > 0; i--)
        largeIntVector.push_back(i);
    RadixSort<int> largeIntSort(largeIntVector, intKey);
    largeIntSort.sort();
    bool isSorted = true;
    for (size_t i = 0; i < largeIntVector.size() - 1; i++) {
        if (largeIntVector[i] > largeIntVector[i + 1]) {
            isSorted = false;
            break;
        }
    }
    passedTests += a_assert(isSorted);
    return std::make_pair(passedTests, 11);
}

int stringKey(const std::string& str) {
    return str.length();
}

std::pair<int, int> radixSortStringVector(){
    int passedTests = 0;
    TestEnvironment env;
    std::vector<std::string> strVec = {"banana", "apple", "cherry", "date", "blueberry"};
    RadixSort<std::string> strSort(strVec, [](const std::string& str) {
        int sum = 0;
        for (char c : str)
            sum += static_cast<int>(c);
        return sum;
    });
    strSort.sort();
    passedTests += a_assert(strVec[0] == "date");
    passedTests += a_assert(strVec[1] == "apple");
    passedTests += a_assert(strVec[2] == "banana");
    passedTests += a_assert(strVec[3] == "cherry");
    passedTests += a_assert(strVec[4] == "blueberry");
    std::vector<std::string> stringVector = {"apple", "banana", "cherry", "date"};
    RadixSort<std::string> stringSort(stringVector, stringKey);
    stringSort.sort();
    passedTests += a_assert(stringVector == std::vector<std::string>({"date", "apple", "banana", "cherry"}));
    return std::make_pair(passedTests, 6);
}

std::pair<int, int> radixSortVectorObject(){
    int passedTests = 0;
    TestEnvironment env;
    std::vector<std::string> data1 = {"apple", "banana", "cherry", "sourcherry"};
    std::vector<std::string> data2 = {"date", "fig", "melon"};
    std::vector<std::string> data3 = {"kiwi", "watermelon"};
    std::vector<std::string> data4 = {"grape"};
    std::vector<std::vector<std::string>> data = {data4, data2, data3, data1};
    RadixSort<std::vector<std::string>> radixSort(data, [](const std::vector<std::string>& vct) {
        return static_cast<int>(vct.size()); });
    radixSort.sort();
    passedTests += a_assert(data[0].size() == 1);
    passedTests += a_assert(data[0][0] == "grape");
    passedTests += a_assert(data[1].size() == 2);
    passedTests += a_assert(data[1][0] == "kiwi");
    passedTests += a_assert(data[2].size() == 3);
    passedTests += a_assert(data[2][0] == "date");
    passedTests += a_assert(data[3].size() == 4);
    passedTests += a_assert(data[3][0] == "apple");
    std::vector<std::vector<std::string>> vectorOfStringVector = {
            {"apple", "banana"}, {"cherry", "date"}, {"grape", "fig", "kiwi"},};
    RadixSort<std::vector<std::string>> vectorOfStringSort(vectorOfStringVector, [](const std::vector<std::string>& vct) {
        int sum = 0;
        for (const std::string& str : vct)
            sum += str.length();
        return sum;
    });
    vectorOfStringSort.sort();
    passedTests += a_assert(vectorOfStringVector == std::vector<std::vector<std::string>>(
            {{"cherry", "date"},
             {"apple",  "banana"},
             {"grape",  "fig", "kiwi"},}));
    return std::make_pair(passedTests, 9);
}

int radixSortTests() {
    int passedTests = 0;
    int totalTests = 0;
    std::pair<int, int> r1 = radixSortNumberVector();
    passedTests += r1.first;
    totalTests += r1.second;
    std::pair<int, int> r2 = radixSortStringVector();
    passedTests += r2.first;
    totalTests += r2.second;
    std::pair<int, int> r3 = radixSortVectorObject();
    passedTests += r3.first;
    totalTests += r3.second;
    double grade = static_cast<double>(passedTests * 100) / totalTests;
    grade = std::round(grade * 10) / 10;
    std::cout << "Total tests passed: " << passedTests << " out of " << totalTests << " (" << grade << "%)"  << std::endl;
    return 0;
}
#endif //RADIXSORTTESTS_H

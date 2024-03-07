/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef MERGESORTTESTS_H
#define MERGESORTTESTS_H
#include <iostream>
#include <cmath>
#include "../include/Utils.h"
#include "../include/MergeSort.h"
#include "TestEnvironment.h"

bool intCompare(const int& a, const int& b) {
    return a < b;
}

bool doubleCompare(const double& a, const double& b) {
    return a < b;
}

std::pair<int, int> mergeSortNumberVector(){
    int passedTests = 0;
    TestEnvironment env;
    std::vector<int> intVec = {5, 2, 9, 3, 6};
    MergeSort<int> intSort([](const int& a, const int& b) { return a < b; });
    intSort.sort(intVec);
    passedTests += a_assert(intVec[0] == 2);
    passedTests += a_assert(intVec[1] == 3);
    passedTests += a_assert(intVec[2] == 5);
    passedTests += a_assert(intVec[3] == 6);
    passedTests += a_assert(intVec[4] == 9);
    std::vector<int> intVector = {43, 12, 7, 65, 23, 9};
    MergeSort<int> intSort2(intCompare);
    intSort2.sort(intVector);
    passedTests += a_assert(intVector == std::vector<int>({7, 9, 12, 23, 43, 65}));
    std::vector<double> doubleVector = {3.14, 1.618, 2.718, 0.577};
    MergeSort<double> doubleSort(doubleCompare);
    doubleSort.sort(doubleVector);
    passedTests += a_assert(doubleVector == std::vector<double>({0.577, 1.618, 2.718, 3.14}));
    std::vector<int> largeIntVector;
    for (int i = 100000; i > 0; i--)
        largeIntVector.push_back(i);
    MergeSort<int> largeIntSort(intCompare);
    largeIntSort.sort(largeIntVector);
    bool isSortedInt = true;
    for (size_t i = 0; i < largeIntVector.size() - 1; i++) {
        if (!intCompare(largeIntVector[i], largeIntVector[i + 1])) {
            isSortedInt = false;
            break;
        }
    }
    passedTests += a_assert(isSortedInt);
    return std::make_pair(passedTests, 8);
}

bool stringCompare(const std::string& a, const std::string& b) {
    return a < b;
}

std::pair<int, int> mergeSortStringVector(){
    int passedTests = 0;
    TestEnvironment env;
    std::vector<std::string> strVec = {"banana", "apple", "cherry", "date", "blueberry"};
    MergeSort<std::string> strSort([](const std::string& a, const std::string& b) { return a < b; });
    strSort.sort(strVec);
    passedTests += a_assert(strVec[0] == "apple");
    passedTests += a_assert(strVec[1] == "banana");
    passedTests += a_assert(strVec[2] == "blueberry");
    passedTests += a_assert(strVec[3] == "cherry");
    passedTests += a_assert(strVec[4] == "date");
    passedTests += a_assert(strVec == std::vector<std::string>({"apple", "banana", "blueberry", "cherry", "date"}));
    std::vector<std::string> largeStringVector;
    for (int i = 10000; i > 0; i--) {
        largeStringVector.push_back("String_" + std::to_string(i));
    }
    MergeSort<std::string> largeStringSort(stringCompare);
    largeStringSort.sort(largeStringVector);
    bool isSortedString = true;
    for (size_t i = 0; i < largeStringVector.size() - 1; i++) {
        if (!stringCompare(largeStringVector[i], largeStringVector[i + 1])) {
            isSortedString = false;
            break;
        }
    }
    passedTests += a_assert(isSortedString);
    return std::make_pair(passedTests, 7);
}

bool bookISBNCompare(const Book& a, const Book& b) {
    return a.ISBN < b.ISBN;
}

bool vectorOfStringKey(const std::vector<std::string>& vec1, const std::vector<std::string>& vec2) {
    int sum1 = 0;
    int sum2 = 0;
    for (const std::string& str : vec1)
        sum1 += str.length();
    for (const std::string& str : vec2)
        sum2 += str.length();
    return sum1 < sum2;
}


std::pair<int, int> mergeSortMoreTests() {
    int passedTests = 0;
    std::vector<std::vector<std::string>> vectorOfStringVector = {
            {"apple", "banana"}, {"cherry", "date"}, {"grape", "fig", "kiwi"},};
    MergeSort<std::vector<std::string>> vectorOfStringSort(vectorOfStringKey);
    vectorOfStringSort.sort(vectorOfStringVector);
    passedTests += a_assert(vectorOfStringVector == std::vector<std::vector<std::string>>(
            {{"cherry", "date"},
             {"apple",  "banana"},
             {"grape",  "fig", "kiwi"},}));
    TestEnvironment env;
    std::vector<Book> bookVector;
    bookVector.push_back(env.book1);
    bookVector.push_back(env.book2);
    bookVector.push_back(env.book3);
    bookVector.push_back(env.book4);
    MergeSort<Book> bookSort(bookISBNCompare);
    bookSort.sort(bookVector);
    bool isSorted = true;
    for (size_t i = 0; i < bookVector.size() - 1; i++) {
        if (!bookISBNCompare(bookVector[i], bookVector[i + 1])) {
            isSorted = false;
            break;
        }
    }
    passedTests += a_assert(isSorted);
    return std::make_pair(passedTests, 2);
}

int mergeSortTests() {
    int passedTests = 0;
    int totalTests = 0;
    std::pair<int, int> r1 = mergeSortNumberVector();
    passedTests += r1.first;
    totalTests += r1.second;
    std::pair<int, int> r2 = mergeSortStringVector();
    passedTests += r2.first;
    totalTests += r2.second;
    std::pair<int, int> r3 = mergeSortMoreTests();
    passedTests += r3.first;
    totalTests += r3.second;
    double grade = static_cast<double>(passedTests * 100) / totalTests;
    grade = std::round(grade * 10) / 10;
    std::cout << "Total tests passed: " << passedTests << " out of " << totalTests << " (" << grade << "%)"  << std::endl;
    return 0;
}

#endif //MERGESORTTESTS_H

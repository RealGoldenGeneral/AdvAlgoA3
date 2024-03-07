/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef LIBRARYRESTRUCTURINGTESTS_H
#define LIBRARYRESTRUCTURINGTESTS_H
#include <iostream>
#include <cmath>
#include "../include/Date.h"
#include "../include/Utils.h"
#include "../include/LibraryRestructuring.h"
#include "TestEnvironment.h"

std::pair<int, int> libraryRestructuringTests1(){
    int passedTests = 0;
    TestEnvironment env;
    UnorderedSet<BorrowRecord> records;
    records.insert(env.record7);
    records.insert(env.record8);
    records.insert(env.record9);
    UnorderedSet<Book> bookCollection;
    bookCollection.insert(env.book1);
    bookCollection.insert(env.book2);
    LibraryRestructuring libraryRestructuring(records, bookCollection);
    HashTable<std::string, UnorderedSet<std::string>>& graph = libraryRestructuring.getGraph();
    passedTests += a_assert(graph[env.book1.ISBN].size() == 1);
    passedTests += a_assert(graph[env.book2.ISBN].size() == 1);
    passedTests += a_assert(graph[env.book1.ISBN].search(env.book2.ISBN));
    passedTests += a_assert(graph[env.book2.ISBN].search(env.book1.ISBN));
    return std::make_pair(passedTests, 4);
}

std::pair<int, int> libraryRestructuringTests2(){
    int passedTests = 0;
    TestEnvironment env;
    UnorderedSet<BorrowRecord> records;
    records.insert(env.record1);
    records.insert(env.record2);
    records.insert(env.record3);
    records.insert(env.record4);
    records.insert(env.record5);
    records.insert(env.record6);
    UnorderedSet<Book> bookCollection;
    bookCollection.insert(env.book1);
    bookCollection.insert(env.book2);
    bookCollection.insert(env.book3);
    bookCollection.insert(env.book4);
    bookCollection.insert(env.book5);
    bookCollection.insert(env.book6);
    LibraryRestructuring libraryRestructuring(records, bookCollection);
    std::vector<std::vector<std::string>> clusters = libraryRestructuring.clusterAndSort("title");
    passedTests += a_assert(clusters.size() == 2);
    for (const auto& cluster : clusters)
        passedTests += a_assert(cluster.size() == 2);
    std::vector<std::string> clusters_0 = clusters[0];
    auto it = std::find(clusters_0.begin(), clusters_0.end(), env.book4.ISBN);
    passedTests += a_assert(it != clusters_0.end());
    auto it2 = std::find(clusters_0.begin(), clusters_0.end(), env.book5.ISBN);
    passedTests += a_assert(it2 != clusters_0.end());

    std::vector<std::string> clusters_1 = clusters[1];
    auto it3 = std::find(clusters_1.begin(), clusters_1.end(), env.book1.ISBN);
    passedTests += a_assert(it3 != clusters_1.end());
    auto it4 = std::find(clusters_1.begin(), clusters_1.end(), env.book2.ISBN);
    passedTests += a_assert(it4 != clusters_1.end());

    return std::make_pair(passedTests, 7);
}

/*
std::pair<int, int> dateDifferenceTests() {
    int passedTests = 0;

    Date startDate1(2023, 7, 19);
    Date endDate1(2023, 7, 19);
    passedTests += assert(Date::diffDuration(startDate1, endDate1) == 0);

    Date startDate2(2023, 7, 15);
    Date endDate2(2023, 7, 20);
    passedTests += assert(Date::diffDuration(startDate2, endDate2) == 5);

    Date startDate3(2023, 6, 15);
    Date endDate3(2023, 7, 7);
    passedTests += assert(Date::diffDuration(startDate3, endDate3) == 22);

    Date startDate4(2023, 7, 19);
    Date endDate4(2023, 7, 18);
    passedTests += assert(Date::diffDuration(startDate4, endDate4) == -1);

    Date startDate5(2020, 6, 15);
    Date endDate5(2021, 6, 15);
    passedTests += assert(Date::diffDuration(startDate5, endDate5) == 366);

    Date startDate6(2022, 6, 15);
    Date endDate6(2023, 6, 15);
    passedTests += assert(Date::diffDuration(startDate6, endDate6) == 365);

    Date startDate7(2022, 6, 15);
    Date endDate7(2024, 6, 15);
    passedTests += a_assert(Date::diffDuration(startDate7, endDate7) == 730);

    return std::make_pair(passedTests, 7);
}
 */

int libraryRestructuringTests() {
    int passedTests = 0;
    int totalTests = 0;
    std::pair<int, int> r1 = libraryRestructuringTests1();
    passedTests += r1.first;
    totalTests += r1.second;
    std::pair<int, int> r2 = libraryRestructuringTests2();
    passedTests += r2.first;
    totalTests += r2.second;
    //std::pair<int, int> r3 = dateDifferenceTests();
    //passedTests += r3.first;
    //totalTests += r3.second;
    double grade = static_cast<double>(passedTests * 100) / totalTests;
    grade = std::round(grade * 10) / 10;
    std::cout << "Total tests passed: " << passedTests << " out of " << totalTests << " (" << grade << "%)"  << std::endl;
    return 0;
}
#endif //LIBRARYRESTRUCTURINGTESTS_H

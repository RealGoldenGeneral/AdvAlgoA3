/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef LIBRARYRESTRUCTURING_H
#define LIBRARYRESTRUCTURING_H
/**
 * Implementation of the library restructuring system main class.
 */
#include <vector>
#include <string>
#include "Utils.h"
#include "UnorderedSet.h"
#include "HashTable.h"
#include "RadixSort.h"
#include "MergeSort.h"

class LibraryRestructuring {
public:
    // TODO implement the following functions in ../src/LibraryRestructuring.cpp
    explicit LibraryRestructuring(const UnorderedSet<BorrowRecord>& records, const UnorderedSet<Book>& bookCollection);
    // Get the graph of books
    HashTable<std::string, UnorderedSet<std::string>>& getGraph() {return graph;}
    // Cluster the graph nodes and sort clusters by average borrowing time, within each cluster, the nodes must be
    // internally sorted based on "sortBy" type which can be one of "title", "author", and "yearPublished"
    // HINT: You need to use both RadixSort and MergeSort implementations for the implementation of clusterAndSort
    std::vector<std::vector<std::string>> clusterAndSort(const std::string& sortBy);

private:
    // Stores the graph representation using an adjacency list
    HashTable<std::string, UnorderedSet<std::string>> graph;
    // Stores the sum of borrowing time for each book
    HashTable<std::string, int> bookBorrowingTime;
    // Stores all the available books in the library, created when the constructor is called
    HashTable<std::string, Book> allBooks;
    // TODO implement the following functions in ../src/LibraryRestructuring.cpp
    // perform a DFS search to find all the nodes connected to the pointed current ISBN
    void dfs(const std::string& current, std::vector<std::string>& cluster, HashTable<std::string, bool>& visited);
    // calculate the average number of days that the books in this cluster has been borrowed
    double getAverageBorrowingTime(const std::vector<std::string>& cluster);
};


#endif //LIBRARYRESTRUCTURING_H

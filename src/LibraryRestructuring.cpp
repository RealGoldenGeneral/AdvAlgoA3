//
// Created by goldengeneral on 24/03/24.
//
#include <vector>
#include <string>
#include "../include/Utils.h"
#include "../include/UnorderedSet.h"
#include "../include/HashTable.h"
#include "../include/RadixSort.h"
#include "../include/MergeSort.h"
#include "../include/Stack.h"
#include "../include/LibraryRestructuring.h"

// Performs a depth first search on the graph.
void LibraryRestructuring::dfs(const std::string &current, std::vector<std::string> &cluster,
                               HashTable<std::string, bool> &visited) {
    visited[current] = true;
    cluster.push_back(current);
    UnorderedSet<std::string>& neighbours = graph[current];
    for (const std::string& neighbour : neighbours) {
        if (!visited[neighbour]) {
            dfs(neighbour, cluster, visited);
        }
    }
}

// Calculates the average borrowing time of a cluster.
double LibraryRestructuring::getAverageBorrowingTime(const std::vector<std::string> &cluster) {
    double totalBorrowingTime = 0.0;
    for (const std::string& ISBN : cluster) {
        totalBorrowingTime += bookBorrowingTime[ISBN];
    }

    return totalBorrowingTime / cluster.size();
}

// Constructs a library restructure. Fills all blocks, book borrowing time, and the graph.
LibraryRestructuring::LibraryRestructuring(const UnorderedSet<BorrowRecord> &records,
                                           const UnorderedSet<Book> &bookCollection) {
    HashTable<std::string, Book> books = HashTable<std::string, Book>(bookCollection.size());
    HashTable<std::string, int> borrowingTime = HashTable<std::string, int>(records.size());
    HashTable<std::string, UnorderedSet<std::string>> borrowGraph = HashTable<std::string, UnorderedSet<std::string>>(
            bookCollection.size());
    for (const Book &book: bookCollection) {
        books.insert(book.ISBN, book);
    }
    for (const BorrowRecord &record: records) {
        UnorderedSet<std::string> edge;
        borrowingTime[record.bookISBN] += Date::diffDuration(record.checkoutDate, record.returnDate);
        for (const BorrowRecord &record1: records) {
            if (record1.bookISBN != record.bookISBN && record1.patronId == record.patronId) {
                edge.insert(record1.bookISBN);
            }
        }
        if (!borrowGraph.search(record.bookISBN)) {
            borrowGraph.insert(record.bookISBN, edge);
        } else {
            borrowGraph[record.bookISBN] = edge;

        }
        allBooks = books;
        bookBorrowingTime = borrowingTime;
        graph = borrowGraph;
    }
}

// Clusters the graph and sorts the clusters by average duration of borrowed time and either title, author,
// or year published,
std::vector<std::vector<std::string>> LibraryRestructuring::clusterAndSort(const std::string &sortBy) {
    HashTable<std::string, bool> visited = HashTable<std::string, bool>(graph.size());
    std::vector<std::vector<std::string>> clusters;

    for (auto bucket: graph) {
        if (!bucket->key.empty()) {
            visited[bucket->key] = false;
        }
    }

    for (auto bucket: graph) {
        if (!bucket->key.empty()) {
            if (!visited[bucket->key]) {
                std::vector<std::string> cluster;
                dfs(bucket->key, cluster, visited);
                if (cluster.size() > 1) {
                    clusters.push_back(cluster);
                }
            }
        }
    }

    RadixSort<std::vector<std::string>> radixSort = RadixSort<std::vector<std::string>>(clusters,
                                                                                        [&](const std::vector<std::string> &cluster) {
                                                                                            return getAverageBorrowingTime(
                                                                                                    cluster);
                                                                                        });
    radixSort.sort();

    for (auto &cluster: clusters) {
        if (sortBy == "title") {
            MergeSort<std::string> mergeSort = MergeSort<std::string>([&](const std::string &a, const std::string &b) {
                return allBooks[a].title < allBooks[b].title;
            });
            mergeSort.sort(cluster);
        } else if (sortBy == "author") {
            MergeSort<std::string> mergeSort = MergeSort<std::string>([&](const std::string &a, const std::string &b) {
                return allBooks[a].author < allBooks[b].author;
            });\
            mergeSort.sort(cluster);
        } else if (sortBy == "yearPublished") {
            MergeSort<std::string> mergeSort = MergeSort<std::string>([&](const std::string &a, const std::string &b) {
                return allBooks[a].yearPublished < allBooks[b].yearPublished;
            });
            mergeSort.sort(cluster);
        }
    }

    return clusters;
}
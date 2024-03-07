/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef HASHTABLE_H
#define HASHTABLE_H
/**
 * Implementation of a hash table.
 */
#include <string>
#include <vector>
#include <limits>
#include <type_traits>

template <typename KeyType, typename ValueType>
class HashTable {
private:
    static constexpr unsigned int HOP_RANGE = 4;

    struct Bucket {
        KeyType key;
        ValueType value;
        bool occupied;
        unsigned int hopInfo;

        Bucket() : occupied(false), hopInfo(0) {}
    };

public:
    unsigned int tableSize;
    double loadFactorThreshold;
    std::vector<Bucket> hashTable;
    class Iterator {
    public:
        Iterator(typename std::vector<Bucket>::iterator current, typename std::vector<Bucket>::iterator end)
                : current(current), end(end) {}

        Iterator& operator++() {
            ++current;
            while (current != end && !current->occupied) {
                ++current;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        typename std::vector<Bucket>::iterator operator*() {
            return current;
        }

    private:
        typename std::vector<Bucket>::iterator current;
        typename std::vector<Bucket>::iterator end;
    };
    // TODO implement the following functions in ../src/HashTable.cpp
    //Hint: you will also need to implement a hashKey function which will allow you to
    // create hash values for different KeyTypes
    explicit HashTable(unsigned int size = 100, double threshold = 0.7);
    Iterator begin();
    Iterator end();
    ValueType& operator[](const KeyType& key);
    void updateValueForKey(const KeyType& key, ValueType newValue);
    void insert(const KeyType& key, const ValueType& value);
    ValueType* search(const KeyType& key);
    bool remove(const KeyType& key);
    void clear();
    unsigned int size() const;
    double loadFactor() const;

private:
    unsigned int hopRange = HOP_RANGE;
    // TODO implement the following functions in ../src/HashTable.cpp
    unsigned int findFreeSlot(std::vector<Bucket>& cTable, unsigned int startIndex, unsigned int& currentHop);
    void rehash();
};

#include "../src/HashTable.cpp"


#endif //HASHTABLE_H
//
// Created by goldengeneral on 04/03/24.
//

#include "../include/HashTable.h"
#include <string>
#include <vector>
#include <limits>
#include <type_traits>


template <typename KeyType>
unsigned int hash(const KeyType& key) {
    unsigned int hash = 0;

    const char* keyString = reinterpret_cast<const char*>(&key);
    for (int i = 0; i < sizeof(KeyType); ++i)  {
        hash = hash * 31 + static_cast<unsigned int>(keyString[i]);
    };
    return hash;
}

template <typename KeyType, typename ValueType>
unsigned int HashTable<KeyType, ValueType>::findFreeSlot(std::vector<Bucket> &cTable, unsigned int startIndex,
                                                         unsigned int &currentHop) {
    // Start from startIndex and try to find free slot within hop range
    for (unsigned int i = 0; i < hopRange; ++i) {
        unsigned int currentIndex = (startIndex + i) % tableSize;
        if (!cTable[currentIndex].occupied) {
            return currentIndex; // Found free slot
        }
    }

    // If no free slot found within hop range, return fail value
    return std::numeric_limits<unsigned int>::max();
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::rehash() {
    // Double size of hash table
    unsigned int newSize = tableSize * 2;
    std::vector<Bucket> newTable(newSize);

    // Update hash table size
    tableSize = newSize;

    // Rehash all elements
    for (auto& bucket : hashTable) {
        if (bucket.occupied) {
            unsigned int originalHash = hash(bucket.key);
            unsigned int hash = originalHash % tableSize;
            unsigned int hopInfo = 0;
            unsigned int index = findFreeSlot(newTable, hash, hopInfo);

            // If we couldn't find free slot, rehash later
            if (index == std::numeric_limits<unsigned int>::max()) {
                continue;
            }

            // Insert the element into the new hash table
            newTable[index].key = std::move(bucket.key);
            newTable[index].value = std::move(bucket.value);
            newTable[index].occupied = true;
            newTable[index].hopInfo = hopInfo;
        }
    }

    // Replace old hash table with new hash table
    hashTable = std::move(newTable);
}

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(unsigned int size, double threshold) {
    tableSize = size;
    loadFactorThreshold = threshold;
    // Initialize hash table with size
    hashTable.resize(tableSize);
}

template <typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::begin() {
    auto it = hashTable.begin();
    auto end = hashTable.end();

    // Skip empty buckets until we find the first occupied one
    while (it != end && !it->occupied) {
        ++it;
    }

    return Iterator(it, end);
}

template <typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::end() {
    return Iterator(hashTable.end(), hashTable.end());
}

template <typename KeyType, typename ValueType>
ValueType &HashTable<KeyType, ValueType>::operator[](const KeyType &key) {
    unsigned int originalHash = hash(key);
    unsigned int hash = originalHash % tableSize; // Calculate hash

    unsigned int index = hash;
    // Search for key in hash table
    for (unsigned int i = 0; i < hopRange; ++i) {
        if (hashTable[index].occupied && hashTable[index].key == key) {
            // If key is found, return its value
            return hashTable[index].value;
        }
        index = (index + 1) % tableSize;
    }

    // If key not found, insert into hash table with default value
    insert(key, ValueType());

    // Retrieve reference to newly inserted value
    return hashTable[originalHash % tableSize].value;
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::updateValueForKey(const KeyType &key, ValueType newValue) {
    // Calculate the hash for key
    unsigned int originalHash = hash(key);
    unsigned int hash = originalHash % tableSize;

    // Find bucket cooresponding to key in hash table
    unsigned int hopInfo = 0;
    while (hopInfo < hopRange && hashTable[hash].key != key) {
        ++hopInfo;
        hash = (hash + 1) % tableSize;
    }

    // If bucket is found and occupied, update value
    if (hopInfo < hopRange && hashTable[hash].occupied) {
        hashTable[hash].value = newValue;
    }
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {
    // Check if load factor exceeds threshold, if it does, rehash
    if ((double)size() / tableSize > loadFactorThreshold) {
        rehash();
    }

    // Calculate hash value of key
    unsigned int hashValue = hash(key);

    // Find free slot for insertion
    unsigned int index = findFreeSlot(hashTable, hashValue, hashValue);

    if (index == std::numeric_limits<unsigned int>::max()) {
        rehash();
        index = findFreeSlot(hashTable, hashValue, hashValue);
    }

    // Update the bucket with key-value pair
    hashTable[index].key = key;
    hashTable[index].value = value;
    hashTable[index].occupied = true;
}

template <typename KeyType, typename ValueType>
ValueType *HashTable<KeyType, ValueType>::search(const KeyType &key) {
    unsigned int originalHash = hash(key);
    unsigned int index = originalHash % tableSize;

    // Probe until we find the key or reach an unoccupied bucket
    unsigned int currentHop = 0;
    while (currentHop < hopRange && hashTable[index].occupied) {
        if (hashTable[index].key == key) {
            return &hashTable[index].value;
        }
        index = (index + 1) % tableSize;
        currentHop++;
    }
    // Key not found
    return nullptr;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::remove(const KeyType &key) {
    unsigned int hashValue = hash(key);
    unsigned int index = hashValue % tableSize;

    // Search for key in hash table
    unsigned int currentHop = 0;
    while (currentHop < hopRange && hashTable[index].occupied) {
        if (hashTable[index].key == key) {
            // Found key, remove it
            hashTable[index].occupied = false;
            return true;
        }
        index = (index + 1) % tableSize;
        currentHop++;
    }

    //Key not found
    return false;
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::clear() {
    for (Bucket& bucket : hashTable)  {
        bucket.occupied = false;
    }
}

template <typename KeyType, typename ValueType>
unsigned int HashTable<KeyType, ValueType>::size() const {
    unsigned int count = 0;
    for (const Bucket& bucket : hashTable) {
        if (bucket.occupied) {
            ++count;
        }
    }
    return count;
}

template <typename KeyType, typename ValueType>
double HashTable<KeyType, ValueType>::loadFactor() const {
    return static_cast<double>(size()) / static_cast<double>(hashTable.size());
}
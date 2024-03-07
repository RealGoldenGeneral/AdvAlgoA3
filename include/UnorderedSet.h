/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef UNORDEREDSET_H
#define UNORDEREDSET_H
/**
 * Implementation of an unordered set using a balanced red-black Tree.
 */
#include <iostream>

enum class Color { RED, BLACK, BLUE };

template <typename Key>
struct Node {
    Key key;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    explicit Node(const Key& k) : key(k), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {}
};

template <typename Key>
class UnorderedSet {
public:
    Node<Key>* root;
    class Iterator {
    public:
        explicit Iterator(Node<Key>* node) : currentNode(node) {}

        bool operator!=(const Iterator& other) const {
            return currentNode != other.currentNode;
        }

        bool operator==(const Iterator& other) const {
            return currentNode == other.currentNode;
        }

        const Key& operator*() const {
            return currentNode->key;
        }

        Iterator& operator++() {
            currentNode = successor(currentNode);
            return *this;
        }

    private:
        Node<Key>* currentNode;

        // Helper function to find the successor of a node
        Node<Key>* successor(Node<Key>* node) const {
            if (node->right != nullptr) {
                node = node->right;
                while (node->left != nullptr)
                    node = node->left;
                return node;
            }

            Node<Key>* parent = node->parent;
            while (parent != nullptr && node == parent->right) {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
    };
    // TODO implement the following functions in ../src/UnorderedSet.cpp
    UnorderedSet();
    ~UnorderedSet();
    Iterator begin() const;
    Iterator end() const;
    bool insert(const Key& key);
    bool search(const Key& key) const;
    bool erase(const Key& key);
    void clear();
    size_t size() const;

private:
    size_t setSize;
    // TODO implement the following functions in ../src/UnorderedSet.cpp
    //Recursively updates the size of the subtree rooted at the given node:
    void updateSize();
    //Recursively calculates the size of the subtree rooted at the given node:
    size_t getSize(Node<Key>* node) const;
    //Fixes a Red-Red violation in the Red-Black Tree:
    void fixRedRedViolation(Node<Key>* node);
    //Performs a left rotation on the subtree rooted at the given node:
    void rotateLeft(Node<Key>* node);
    //Performs a right rotation on the subtree rooted at the given node:
    void rotateRight(Node<Key>* node);
    //Deletes a node with only one child in the Red-Black Tree:
    void deleteOneChild(Node<Key>* node);
    //Fixes the Red-Black Tree properties after a node deletion:
    void deleteFix(Node<Key>* node);
    //Recursively clears the Red-Black Tree starting from the given node:
    void clearRecursive(Node<Key>* node);
};

#include "../src/UnorderedSet.cpp"

#endif //UNORDEREDSET_H
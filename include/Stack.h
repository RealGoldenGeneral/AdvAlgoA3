/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef STACK_H
#define STACK_H
/**
 * Implementation of an unordered set using a balanced Tree.
 */
#include <vector>
#include <cstddef>

template <typename T>
class Stack {
public:
    // TODO implement the following functions in ../src/Stack.cpp
    Stack();
    bool isEmpty() const;
    size_t size() const;
    void push(const T& element);
    void pop();
    T& top();
    const T& top() const;

private:
    std::vector<T> buffer;
    size_t currentSize;
};

#include "../src/Stack.cpp"

#endif //STACK_H
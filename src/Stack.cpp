#include <vector>
#include "../include/Stack.h"

// Creates a stack with an empty vector buffer.
template <typename T>
Stack<T>::Stack() {
    buffer = std::vector<T>();
    currentSize = buffer.size();
}

// Checks if the stack is empty and returns true or false.
template <typename T>
bool Stack<T>::isEmpty() const {
    return buffer.empty();
}

// Returns the size of the stack.
template <typename T>
size_t Stack<T>::size() const {
    return currentSize;
}

// Pushes an element to the top of the stack.
template <typename T>
void Stack<T>::push(const T &element) {
    buffer.push_back(element);
    currentSize = buffer.size();
}

// Pops the top element from the stack.
template <typename T>
void Stack<T>::pop() {
    buffer.pop_back();
    currentSize = buffer.size();
}

// Returns the top element from the stack.
template <typename T>
T &Stack<T>::top() {
    return buffer.back();
}

// Returns the top element from the stack.
template <typename T>
const T &Stack<T>::top() const {
    return buffer.back();
}
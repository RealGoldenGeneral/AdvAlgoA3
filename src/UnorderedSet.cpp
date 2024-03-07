#include "../include/UnorderedSet.h"
#include <iostream>

template <typename Key>
void UnorderedSet<Key>::updateSize() {
    setSize = getSize(root);
}

template <typename Key>
size_t UnorderedSet<Key>::getSize(Node<Key>* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getSize(node->left) + getSize(node->right);
}

template <typename Key>
void UnorderedSet<Key>::deleteOneChild(Node<Key>* node) {
    // Ensure that node and child are not null
    if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
        return;
    }

    // Get child of node
    Node<Key>* child;
    if (node->right == nullptr) {
        child = node->left;
    } else {
        child = node->right;
    }

    // If node is root, delete the node
    if (node == root) {
        root = child;
        if (root != nullptr) {
            root->parent = nullptr;
        }
        delete node;
        return;
    }

    // Fix the parent pointer of the child
    child->parent = node->parent;

    // Fix the parent's child pointer
    if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    // If deleted node is black, fix Red-Black Tree properties
    if (node->color == Color::BLACK) {
        // If child is red, repaint black
        if (child->color == Color::RED) {
            child->color = Color::BLACK;
        } else {
            // If child is black, fix double black
            deleteFix(child);
        }
    }
    delete node;
}

template <typename Key>
void UnorderedSet<Key>::deleteFix(Node<Key>* node) {
    while (node != root && (node == nullptr || node->color == Color::BLACK)) {
        if (node == node->parent->left) {
            Node<Key>* sibling = node->parent->right;

            // Recolour and rotate left if sibling is red
            if (sibling->color == Color::RED) {
                sibling->color = Color::BLACK;
                node->parent->color = Color::RED;
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }

            // Recolour sibling to red if sibling left or right child is black
            if ((sibling->left == nullptr || sibling->left->color == Color::BLACK) &&
                (sibling->right == nullptr || sibling->right->color == Color::BLACK)) {
                sibling->color = Color::RED;
                node = node->parent;
            } else {
                // Recolour sibling left child to black and sibling to red and rotate right if
                // sibling right child is black
                if (sibling->right == nullptr || sibling->right->color == Color::BLACK) {
                    sibling->left->color = Color::BLACK;
                    sibling->color = Color::RED;
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }

                // Recolour sibling to parent colour, parent colour to black, and sibling right child to black
                // and rotate left
                sibling->color = node->parent->color;
                node->parent->color = Color::BLACK;
                sibling->right->color = Color::BLACK;
                rotateLeft(node->parent);
                node = root;
            }
        } else {
            Node<Key>* sibling = node->parent->left;

            // If sibling is red, recolour sibling to black and parent to black and rotate right
            if (sibling->color == Color::RED) {
                sibling->color = Color::BLACK;
                node->parent->color = Color::RED;
                rotateRight(node->parent);
                sibling = node->parent->left;
            }

            // If sibling left or right children are black, recolour sibling color to red
            if ((sibling->right == nullptr || sibling->right->color == Color::BLACK) &&
                (sibling->left == nullptr || sibling->left->color == Color::BLACK)) {
                sibling->color = Color::RED;
                node = node->parent;
            } else {
                // If sibling left child is black, recolour sibling right child to black and sibling to red
                // and rotate left
                if (sibling->left == nullptr || sibling->left->color == Color::BLACK) {
                    sibling->right->color = Color::BLACK;
                    sibling->color = Color::RED;
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }
                // Recolour sibling to parent colour, parent to black, and sibling left child to black
                sibling->color = node->parent->color;
                node->parent->color = Color::BLACK;
                sibling->left->color = Color::BLACK;
                rotateRight(node->parent);
                node = root;
            }
        }
    }

    // If node is not null, recolour to black
    if (node != nullptr)
        node->color = Color::BLACK;
}

template <typename Key>
void UnorderedSet<Key>::clearRecursive(Node<Key> *node) {
    if (node == nullptr) {
        return;
    }

    // Recursively clear the left subtree
    clearRecursive(node->left);
    // Recursively clear the right subtree
    clearRecursive(node->right);

    // Delete current node
    delete node;
}

template <typename Key>
void UnorderedSet<Key>::rotateRight(Node<Key>* node) {
    if (node == nullptr || node->left == nullptr) {
        return;
    }

    Node<Key>* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->right) {
        node->parent->right = leftChild;
    } else {
        node->parent->left = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

template <typename Key>
void UnorderedSet<Key>::rotateLeft(Node<Key>* node) {
    if (node == nullptr || node->right == nullptr) {
        return;
    }

    Node<Key>* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

template <typename Key>
void UnorderedSet<Key>::fixRedRedViolation(Node<Key>* node) {
    Node<Key>* parent;
    Node<Key>* grandparent;

    while (node != root && node->color == Color::RED && node->parent->color == Color::RED) {
        parent = node->parent;
        grandparent = parent->parent;

        // Case 1: Parent is the left child of grandparent
        if (parent == grandparent->left) {
            Node<Key>* uncle = grandparent->right;

            // Case 1a: Uncle is also red
            if (uncle && uncle->color == Color::RED) {
                // Change color of parent and uncle to black
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                // Change color of grandparent to red
                grandparent->color = Color::RED;
                // Move up the tree for further fixing
                node = grandparent;
            } else {
                // Case 1b: Uncle is black or null, and node is the right child of parent
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                // Case 1c: Uncle is black or null, and node is the left child of parent
                parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateRight(grandparent);
            }
        } else { // Parent is the right child of grandparent
            Node<Key>* uncle = grandparent->left;
            if (uncle && uncle->color == Color::RED) {
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateLeft(grandparent);
            }
        }
    }

    root->color = Color::BLACK; // Ensure the root is always black
}


template <typename Key>
UnorderedSet<Key>::UnorderedSet() {
    setSize = 0;
    root = nullptr;
}

template <typename Key>
UnorderedSet<Key>::~UnorderedSet() {
    clear();
}

template <typename Key>
typename UnorderedSet<Key>::Iterator UnorderedSet<Key>::begin() const {
    Node<Key>* currentNode = root;
    while (currentNode != nullptr && currentNode->left != nullptr) {
        currentNode = currentNode->left;
    }
    return Iterator(currentNode);
}

template <typename Key>
typename UnorderedSet<Key>::Iterator UnorderedSet<Key>::end() const {
    return Iterator(nullptr);
}

template <typename Key>
bool UnorderedSet<Key>::insert(const Key &key) {
    Node<Key>* newNode = new Node<Key>(key); // Creates new node with key
    Node<Key>* parent = nullptr;
    Node<Key>* current = root;

    // Traverse the tree to place new node
    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            // If key already exists, do not insert
            delete newNode;
            return false;
        }
    }

    // Set parent of new node
    newNode->parent = parent;

    // Determine placement of new node
    if (parent == nullptr) {
        // If empty tree, new node is root
        root = newNode;
    } else if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Perform necessary operations to maintain red-black tree properties
    fixRedRedViolation(newNode);

    // Increment size of set
    setSize++;

    return true;
}

template <typename Key>
bool UnorderedSet<Key>::search(const Key &key) const {
    Node<Key>* current = root;

    // Traverse the tree to look for key
    while (current != nullptr) {
        if (key == current->key) {
            return true; // Key found
        } else if (key < current->key) {
            current = current->left; // Move to left subtree
        } else {
            current = current->right; // Move to right subtree
        }
    }

    return false; // Key not found
}

template <typename Key>
bool UnorderedSet<Key>::erase(const Key &key) {
    Node<Key>* nodeToDelete = root;
    Node<Key>* parent = nullptr;

    // Find node to delete
    while (nodeToDelete != nullptr) {
        if (key == nodeToDelete->key) {
            break; // Found node to delete
        }
        parent = nodeToDelete;
        if (key < nodeToDelete->key) {
            nodeToDelete = nodeToDelete->left; // Move to left subtree
        } else {
            nodeToDelete = nodeToDelete->right; // Move to right subtree
        }
    }

    if (nodeToDelete == nullptr) {
        return false; // Key not found
    }

    // Node to delete has two children
    if (nodeToDelete->left != nullptr && nodeToDelete->right != nullptr) {
        // Find successor node
        Node<Key>* successor = nodeToDelete->right;
        while (successor->left != nullptr) {
            successor = successor->left;
        }

        // Copy the successor's key to delete
        nodeToDelete->key = successor->key;

        // Update node to delete and parent
        parent = successor->parent;
        nodeToDelete = successor;
    }

    // Node to delete has one child at most
    Node<Key>* child;
    if (nodeToDelete->left != nullptr) {
        child = nodeToDelete->left;
    } else {
        child = nodeToDelete->right;
    }

    // If the node to delete is red or its child is red
    if (nodeToDelete->color == Color::RED || (child != nullptr && child->color == Color::RED)) {
        // Replaced node to delete with child
        if (nodeToDelete == root)  {
            root = child;
        } else if (nodeToDelete == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }

        if (child != nullptr) {
            child->parent = parent;
            child->color = Color::BLACK;
        }

        delete nodeToDelete;
    } else {
        deleteOneChild(nodeToDelete);
        if (nodeToDelete == root) {
            root = nullptr;
        }
    }

    setSize--;
    return true;
}

template <typename Key>
void UnorderedSet<Key>::clear() {
    clearRecursive(root);
    root = nullptr;
    setSize = 0;
}

template <typename Key>
size_t UnorderedSet<Key>::size() const {
    return setSize;
}
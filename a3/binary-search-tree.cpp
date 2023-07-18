#include "binary-search-tree.h"
#include <algorithm>
#include <iostream>
#include <queue>


BinarySearchTree::Node::Node(DataType newval) {
    val = newval;
    left = nullptr;
    right = nullptr;
    avlBalance = 0;
}


int BinarySearchTree::getNodeDepth(Node* n) const {
    if (n == nullptr) {
        return -1;
    } else {
        int left_depth = getNodeDepth(n->left);
        int right_depth = getNodeDepth(n->right);
        return std::max(left_depth,right_depth) + 1;
    }
}

BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
    size_ = 0;
}



BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::recursiveDelete(root_);
}

void BinarySearchTree::recursiveDelete(Node *node) {
    if (node != nullptr) {
        recursiveDelete(node->left);
        recursiveDelete(node->right);
        delete node;
    }
}



unsigned int BinarySearchTree::size() const {
    return size_;
}


BinarySearchTree::DataType BinarySearchTree::max() const {
    Node* node = root_;
    while (node->right != nullptr) {
        node = node->right;
    }
    return node->val;
}


BinarySearchTree::DataType BinarySearchTree::min() const {
    Node* curr = root_;
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr->val;
}


unsigned int BinarySearchTree::depth() const {
    return getNodeDepth(root_);
}

//void BinarySearchTree::print() const


bool BinarySearchTree::exists(DataType val) const {
    Node* current = root_;
    while (current != nullptr) {
        if (val == current->val) {
            return true;
        } else if (val < current->val) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}


BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}



BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

BinarySearchTree::Node* BinarySearchTree::getNode(DataType val){
    Node *n = root_;
    Node *parent = nullptr;
    bool isLeftChild = false;

    while (n != nullptr) {
        if (val == n->val) {
            break;
        } else if (val < n->val) {
            parent = n;
            n = n->left;
            isLeftChild = true;
        } else {
            parent = n;
            n = n->right;
            isLeftChild = false;
        }
    }
    return (n);
}


bool BinarySearchTree::insert(DataType val) {
    Node *newNode = new Node(val);

    if (root_ == nullptr) {
        root_ = newNode;
        size_++;
        return true;
    }

    Node *currentNode = root_;
    while (currentNode != nullptr) {

        if (val == currentNode->val) {
            delete newNode;
            return false;
        } else if (val < currentNode->val) {
            if (currentNode->left == nullptr) {
                currentNode->left = newNode;
                size_++;
                return true;
            } else {
                currentNode = currentNode->left;
            }
        } else {
            if (currentNode->right == nullptr) {
                currentNode->right = newNode;
                size_++;
                return true;
            } else {
                currentNode = currentNode->right;
            }
        }
    }

    return false;
}



bool BinarySearchTree::remove(DataType val) {
    Node *currentNode = root_;
    Node *parent = nullptr;
    bool isLeftChild = false;

    // Find the node with the given value
    while (currentNode != nullptr) {
        if (val == currentNode->val) {
            break;
        } else if (val < currentNode->val) {
            parent = currentNode;
            currentNode = currentNode->left;
            isLeftChild = true;
        } else {
            parent = currentNode;
            currentNode = currentNode->right;
            isLeftChild = false;
        }
    }

    // If the node is not found, return false
    if (currentNode == nullptr) {
        return false;
    }

    // If the node has two children, replace the value with the predecessor
    if (currentNode->left != nullptr && currentNode->right != nullptr) {
        Node *predecessor = currentNode->left;
        Node *predecessorParent = currentNode;
        while (predecessor->right != nullptr) {
            predecessorParent = predecessor;
            predecessor = predecessor->right;
        }
        currentNode->val = predecessor->val;
        if (predecessorParent == currentNode) {
            currentNode->left = predecessor->left;
        } else {
            predecessorParent->right = predecessor->left;
        }
        delete predecessor;
        size_--;
        return true;
    }

    // If the node is a leaf node
    if (currentNode->left == nullptr && currentNode->right == nullptr) {
        if (currentNode == root_) {
            root_ = nullptr;
        } else if (isLeftChild) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete currentNode;
        size_--;
        return true;
    }

    // If the node has one child
    if (currentNode->left == nullptr && currentNode->right != nullptr) {
        if (currentNode == root_) {
            root_ = currentNode->right;
        } else if (isLeftChild) {
            parent->left = currentNode->right;
        } else {
            parent->right = currentNode->right;
        }
        delete currentNode;
        size_--;
        return true;

    } else if (currentNode->left != nullptr && currentNode->right == nullptr) {
        if (currentNode == root_) {
            root_ = currentNode->left;
        } else if (isLeftChild) {
            parent->left = currentNode->left;
        } else {
            parent->right = currentNode->left;
        }
        delete currentNode;
        size_--;
        return true;
    }
}



void BinarySearchTree::printBFT(){
    if(root_ == nullptr) {
        std::cout << "Tree is empty." << std::endl;
        return;
    }
    std::queue <Node*> Q;
    Q.push(root_);
    while (!Q.empty()) {
        Node *P = Q.front();
        Q.pop();
        std::cout<< P->val<<", ";
        if (P->left != nullptr) Q.push(P->left);
        if (P->right != nullptr) Q.push(P->right);
    }
    std::cout << std::endl;
}

void BinarySearchTree::updateNodeBalance(Node* n) {
    if (n == nullptr) {
        return;
    }

    int left_depth = getNodeDepth(n->left);
    int right_depth = getNodeDepth(n->right);
    n->avlBalance = right_depth - left_depth;

    updateNodeBalance(n->left);
    updateNodeBalance(n->right);
}







#ifndef LAB3_AVL_TREE_H
#define LAB3_AVL_TREE_H

#include "binary-search-tree.h"

class AVLTree : public BinarySearchTree {
public:
    // Overriden insert and remove functions
    // Do not modify these definitions

    // The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    int Height(BinarySearchTree::Node *T);
    void SingleRightRotation (BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha);
    void SingleLeftRotation (BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha);
    void LeftRightRotation (BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha);
    void RightLeftRotation (BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha);

    bool remove(DataType val);


    // Define additional functions and attributes below if you need
};

#endif  // LAB3_AVL_TREE_H

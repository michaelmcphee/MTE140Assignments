#include "avl-tree.h";
#include <iostream>



bool AVLTree::insert(DataType val){

    bool result = BinarySearchTree::insert(val);

    if(result == false) return false;


    Node* root = *getRootNodeAddress();

    if(root->val == val) return true;

    Node *temp;
    temp = root;
    Node *temp_parent;
    Node *alpha = NULL;

    do{
        temp_parent = temp;
        if(val > temp->val) temp = temp->right;
        else if (val < temp->val) temp =  temp->left;
        int leftHeight = Height(temp_parent->left);
        int rightHeight = Height(temp_parent->right);
        if( abs(leftHeight - rightHeight) >= 2 ) alpha = temp_parent;

    } while ( temp->val != val );

    if(!alpha) return true;

    if     (val < alpha->val && val < alpha->left->val  ) SingleRightRotation (getRootNodeAddress(), alpha);
    else if (val > alpha->val && val > alpha->right->val ) SingleLeftRotation(getRootNodeAddress(), alpha);
    else if (val < alpha->val && val > alpha->left->val ) LeftRightRotation(getRootNodeAddress(), alpha);
    else if (val > alpha->val && val < alpha->right->val ) RightLeftRotation(getRootNodeAddress(), alpha);

    return true;
}

int AVLTree::Height(BinarySearchTree::Node *T){
    if(T == NULL) return -1;
    else if (T->left == NULL && T->right == NULL) return 0;
    else {
        return 1 + std::max(Height(T->left), Height(T->right) );
    }
}


void AVLTree::SingleRightRotation (BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha){

    BinarySearchTree::Node *A = alpha->left;

    alpha->left = A->right;

    A->right = alpha;

    if (*pT == alpha) {
        *pT = A;
    }
    else {

        BinarySearchTree::Node *temp = *pT;
        BinarySearchTree::Node **parentPointerToAlpha = NULL;
        do{
            if(alpha->val > temp->val)  {
                parentPointerToAlpha = &temp->right;
                temp = temp->right;
            }
            else if (alpha->val < temp->val) {
                parentPointerToAlpha = &temp->left;
                temp = temp->left;
            }
        }
        while (temp->val != alpha->val);

        *parentPointerToAlpha = A;
    }
}


void AVLTree::SingleLeftRotation (BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha){

    BinarySearchTree::Node *A = alpha->right;

    alpha->right = A->left;

    A->left = alpha;

    if (*pT == alpha) {
        *pT = A;
    }
    else {

        BinarySearchTree::Node *temp = *pT;
        BinarySearchTree::Node **parentPointerToAlpha = NULL;
        do{
            if(alpha->val > temp->val)  {
                parentPointerToAlpha = &temp->right;
                temp = temp->right;
            }
            else if (alpha->val < temp->val) {
                parentPointerToAlpha = &temp->left;
                temp = temp->left;
            }
        }
        while (temp->val != alpha->val);

        *parentPointerToAlpha = A;
    }
}


void AVLTree::LeftRightRotation (BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha){

    BinarySearchTree::Node *A = alpha->left;

    SingleLeftRotation(pT, A);

    SingleRightRotation(pT, alpha);
}


void AVLTree::RightLeftRotation (BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha){

    BinarySearchTree::Node *A = alpha->right;

    SingleRightRotation(pT, A);

    SingleLeftRotation(pT, alpha);
}

bool AVLTree::remove(DataType val) {
    
}


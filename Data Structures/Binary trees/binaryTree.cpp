//
// Created by Raffaele on 11/03/2023.
//
#include <iostream>
#include <cstdlib>
#include "binaryTree.h"

BinaryTree *createTree(int info) {
    auto *root = new BinaryTree;
    root->info = info;
    root->left = nullptr;
    root->right = nullptr;
    return root;
}

void insert(BinaryTree* root, int info, string mode) {
    //TODO: inutile
    BinaryTree *ptr = root;

    if(mode[0] == 'l') {
        while(ptr->left != nullptr) {
            ptr = ptr->left;
        }


        if(mode[1] == 'l') {
            ptr->left = new BinaryTree;
            ptr->left->info = info;
            ptr->left->left = nullptr;
            ptr->left->right = nullptr;
        }
        else {
            ptr->right = new BinaryTree;
            ptr->right->info = info;
            ptr->right->left = nullptr;
            ptr->right->right = nullptr;
        }
    }
    else {
        while(ptr->right != nullptr) {
            ptr = ptr->right;
        }

        if(mode[1] == 'l') {
            ptr->left = new BinaryTree;
            ptr->left->info = info;
            ptr->left->left = nullptr;
            ptr->left->right = nullptr;
        }

        else {
            ptr->right = new BinaryTree;
            ptr->right->info = info;
            ptr->right->left = nullptr;
            ptr->right->right = nullptr;
        }
    }
}

void inOrder(BinaryTree* root) {
    if(root != nullptr)
    {
        inOrder(root->left);
        cout << root->info << " ";
        inOrder(root->right);
    }
}

void preOrder(BinaryTree *root) {
    if(root != nullptr) {
        cout << root->info << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(BinaryTree *root) {
    if(root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->info << " ";
    }
}


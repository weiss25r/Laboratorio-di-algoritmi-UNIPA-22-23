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

void insertRightTo(BinaryTree *node, int info) {
    auto newNode = createTree(info);
    node->right = newNode;
}

void insertLeftTo(BinaryTree *node, int info) {
    auto newNode = createTree(info);
    node->left = newNode;
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

BinaryTree *createMirror(BinaryTree* root) {
    //base della ricorsione: root è una foglia
    if(root == nullptr) {
        return nullptr;
    }
    else if(root->left == nullptr && root->right == nullptr) {
        return createTree(root->info);
    }
    else {
        BinaryTree *left = createMirror(root->left);
        BinaryTree *right = createMirror(root->right);
        BinaryTree *node = createTree(root->info);
        node->left = right;
        node->right = left;

        return node;
    }
}

void convertToMirror(BinaryTree* root) {
    //base: se è una foglia non c'è nulla da fare

    if(root == nullptr || (root->left == nullptr && root->right == nullptr)) {
        return;
    }
    else{
        convertToMirror(root->left);
        convertToMirror(root->right);

        BinaryTree *tmp = root->left;
        root->left = root->right;
        root->right = tmp;
    }
}

BinaryTree *createFrom(int *preOrder, int *inOrder, int lp, int rp, int li, int ri) {
    if(lp > rp) {
        return nullptr;
    }
    else {
        int j;

        for(j = li; j <= ri && inOrder[j] != preOrder[lp]; j++);

        if(j <= ri) {
            BinaryTree *c = createTree(preOrder[lp]);
            BinaryTree *a = createFrom(preOrder, inOrder, lp+1, rp-j, li, j-1);
            BinaryTree *b = createFrom(preOrder, inOrder, rp-j+1, rp, j+1, ri);
            c->left = a;
            c->right = b;
            return c;
        } else return nullptr;
    }
}
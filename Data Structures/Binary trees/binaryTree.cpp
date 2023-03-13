//
// Created by Raffaele on 11/03/2023.
//
#include <iostream>
#include <cstdlib>
#include "binaryTree.h"

int pIndex = 0;

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

//O(N^2)?
BinaryTree *createFrom(int *preOrder, int *inOrder, int rp, int li, int ri){

    if(li > ri || pIndex>rp) {
        return nullptr;
    }
    else {
        int j;

        for(j = li; j <= ri && inOrder[j] != preOrder[pIndex]; j++);

        if(j <= ri) {
            BinaryTree *c = createTree(preOrder[pIndex]);
            pIndex++;

            BinaryTree *a = createFrom(preOrder, inOrder, rp, li, j-1);
            BinaryTree *b = createFrom(preOrder, inOrder, rp, j+1, ri);
            c->left = a;
            c->right = b;
            return c;
        } else return nullptr;
    }
}

int min(int *array, int left, int right) {
    int m = left;

    for (int i = left; i <= right; ++i) {
        if(array[i] < array[m]) {
            m = i;
        }
    }

    return m;
}


//T(n) = T(n-1)+O(n) = O(n^2)
BinaryTree *createArchimedeOne(int *sequence, int left, int right) {
    if(left == right) {
        return createTree(sequence[left]);
    }
    else if(left > right){
        return nullptr;
    }
    else {
        int m = min(sequence, left, right);

        BinaryTree *a = createArchimedeOne(sequence, left, m-1);
        BinaryTree *b = createArchimedeOne(sequence, m+1, right);

        BinaryTree *node = createTree(sequence[m]);
        node->left = a;
        node->right = b;

        return node;
    }
}


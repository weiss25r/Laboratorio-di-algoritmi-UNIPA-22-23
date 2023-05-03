//
// Created by weiss on 27/04/23.
//

#ifndef SEARCH_TREES_FSTTREE_H
#define SEARCH_TREES_FSTTREE_H

#include "BstTree.h"
#include <iostream>
/* A Fog Search Tree is a splay tree that uses the "Move to root" method */

template <class T>

class FstTree {
public:
    FstTree() { root = nullptr; }

    explicit FstTree(T rootKey) {
        root = nullptr;
        insertHelper(root, rootKey);
    };

    bool search(T key);

    void insert(T info);

    void remove(T key);

    void inOrder();

    //..

    ~FstTree() {
        deleteTree(root);
    };

private:
    Node<T> *root;

    void insertHelper(Node<T> *&rootNode, T info);

    void removeHelper(Node<T> *&rootNode, T info);

    void rotateRight(Node<T> *&node);

    void rotateLeft(Node<T> *&node);

    bool fogSearch(Node<T> *&node, T key);

    void deleteTree(Node<T> *&rootNode);

    void inOrderHelper(Node<T> *root);

    Node<T> *&minHelper(Node<T> *&rootNode);
};

#endif //SEARCH_TREES_FSTTREE_H
#include "FstTree.cpp"
//
// Created by weiss on 27/04/23.
//

#ifndef SEARCH_TREES_FSTTREE_H
#define SEARCH_TREES_FSTTREE_H

#include "BstTree.h"

/* A Fog Search Tree is a splay tree that uses the "Move to root" method */

class FstTree {

public:
    FstTree() { root = nullptr; }

    explicit FstTree(int rootKey);

    bool search(int key);

    void insert(int info);

    void remove(int key);

    void inOrder();

    //..

    ~FstTree();

private:
    Node *root;

    void insertHelper(Node *&rootNode, int info);

    void removeHelper(Node *&rootNode, int info);

    void rotateRight(Node *&node);

    void rotateLeft(Node *&node);

    bool fogSearch(Node *&node, int key);

    void deleteTree(Node *&rootNode);

    void inOrderHelper(Node *root);

    Node *&minHelper(Node *&rootNode);

    //..

};

#endif //SEARCH_TREES_FSTTREE_H

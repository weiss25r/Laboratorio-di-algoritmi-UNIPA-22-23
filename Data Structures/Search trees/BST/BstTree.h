//
// Created by Raffaele on 21/04/2023.
//

#ifndef BST_BSTTREE_H
#define BST_BSTTREE_H

#include <iostream>
#include <vector>
#include <ostream>

template <class T>
struct Node {
    T info;
    int height;
    Node *left;
    Node *right;

    Node(int info, int height, Node *left, Node *right) : info(info), height(height), left(left), right(right) {}
};

template <class T>

class BstTree {

public:
    BstTree() {root = nullptr;}
    explicit BstTree(T rootKey);
    explicit BstTree(const std::vector<T> &keys);
    BstTree(const BstTree &bst);
    virtual void insert(int info);
    bool search(int key) const;
    virtual void remove(int key);
    T max();
    T min();
    int getHeight() const;
    void inOrder() const;
    void preOrder() const;
    void postOrder() const;
    bool isEmpty() const {return root == nullptr;}
    BstTree& operator=(const BstTree& bst);
    ~BstTree();

    template <class U>
    friend std::ostream &operator<< (std::ostream &os, const BstTree<U> &bst);

protected:
    Node<T> *root;
    virtual void insertHelper(Node<T>* &rootNode, int info);
    virtual void removeHelper(Node<T> *&rootNode, int info);
    bool searchHelper(Node<T> *rootNode, int info) const;
    Node<T> *maxHelper(Node<T> *rootNode) const;
    Node<T> *&minHelper(Node<T> *&rootNode);
    void inOrderHelper(Node<T> * rootNode) const;
    void preOrderHelper(Node<T> * rootNode) const;
    void postOrderHelper(Node<T> * rootNode) const;
    void deleteTree(Node<T> *&rootNode);
    int assignHeight(Node<T> *node);
    void copyHelper(Node<T> *&rootOne, Node<T> *rootTwo);
};

#endif //BST_BSTTREE_H

#include "BstTree.cpp"

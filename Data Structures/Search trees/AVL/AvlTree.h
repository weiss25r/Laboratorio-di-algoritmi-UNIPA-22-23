//
// Created by Raffaele on 24/04/2023.
//

#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H

#include "../BST/BstTree.h"

template <class T>

class AvlTree : public BstTree<T>{
public:
    AvlTree() : BstTree<T>() {};
    explicit AvlTree(T rootKey);
    explicit AvlTree(const std::vector<T> &keys);

    void insert(T info) override;
    void remove(T info) override;

    //more costructors and operators...
private:
    void rotateLeft(Node<T> *& node);
    void rotateRight(Node<T> *& node);
    void fixTree(Node<T> *&node, int direction);
    int getNodeHeight(Node<T> *node);

protected:
    void insertHelper(Node<T> *&rootNode, int info) override;
    void removeHelper(Node<T> *&rootNode, int info) override;
};


#endif //AVL_AVLTREE_H

#include "AvlTree.cpp"
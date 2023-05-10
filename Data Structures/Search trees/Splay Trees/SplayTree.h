//
// Created by Raffaele on 28/04/2023.
//

#ifndef SEARCH_TREES_SPLAYTREE_H
#define SEARCH_TREES_SPLAYTREE_H

//Self adjusting binary trees, introduced by Tarjan and Sleator in 1985

template <typename T>

struct SplayNode
{
    T info;
    SplayNode *left;
    SplayNode *right;
    SplayNode *parent;

    SplayNode(T info, SplayNode *left, SplayNode *right, SplayNode *parent) : info(info), left(left), right(right),
                                                                              parent(parent) {}
};

template <typename T>
class SplayTree {
public:
    SplayTree();

    ~SplayTree();

    void inOrder();
    void preOrder();

    void climbInsert(const T &key);
protected:
    SplayNode<T> *root;
private:
    void inOrderHelper(SplayNode<T> *tree);
    void preOrderHelper(SplayNode<T> *tree);

    void rotateLeft(SplayNode<T> *node);
    void rotateRight(SplayNode<T> *node);
    void climb(SplayNode<T> *node);

    void deleteTree(SplayNode<T> *&rootNode);
};




template<typename T>
SplayTree<T>::~SplayTree() {
    deleteTree(root);
}


#endif //SEARCH_TREES_SPLAYTREE_H
#include "SplayTree.cpp"
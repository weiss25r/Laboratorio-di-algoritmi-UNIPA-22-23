//
// Created by Raffaele on 24/04/2023.
//

#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H

#include "../BST/BstTree.h"

class AvlTree : public BstTree{
public:
    AvlTree() : BstTree() {};
    explicit AvlTree(int rootKey);
    explicit AvlTree(const std::vector<int> &keys);

    void insert(int info) override;
    void remove(int info) override;
    //others costructor and operators...
private:
    void rotateLeft(Node *& node);
    void rotateRight(Node *& node);
    void fixTree(Node *&node, int direction);
    int getNodeHeight(Node *node);

protected:
    void insertHelper(Node *&rootNode, int info) override;
    void removeHelper(Node *&rootNode, int info) override;
};


#endif //AVL_AVLTREE_H

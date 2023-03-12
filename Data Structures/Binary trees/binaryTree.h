//
// Created by Raffaele on 11/03/2023.
//

#ifndef LABORATORIO_DI_ALGORITMI_UNIPA_22_23_BINARYTREE_H
#define LABORATORIO_DI_ALGORITMI_UNIPA_22_23_BINARYTREE_H

#endif //LABORATORIO_DI_ALGORITMI_UNIPA_22_23_BINARYTREE_H

#include <string>

using namespace std;

struct BinaryTree {
    int info;
    BinaryTree *left;
    BinaryTree *right;
};

BinaryTree *createTree(int info);
void insertRightTo(BinaryTree *node, int info);
void insertLeftTo(BinaryTree *node, int info);
bool isEmpty(BinaryTree* root);
void inOrder(BinaryTree* root);
void preOrder(BinaryTree* root);
void postOrder(BinaryTree* root);
void isLinear(BinaryTree* root);
int getHeight(BinaryTree* root);
BinaryTree *createMirror(BinaryTree* root);
void convertToMirror(BinaryTree* root);
BinaryTree *createFrom(int *preOrder, int *inOrder, int lp, int rp, int li, int ri);
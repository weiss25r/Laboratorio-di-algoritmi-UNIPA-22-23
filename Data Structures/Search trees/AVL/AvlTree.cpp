//
// Created by Raffaele on 24/04/2023.
//

#include "AvlTree.h"

AvlTree::AvlTree(int rootKey) : BstTree(rootKey) {}

void AvlTree::rotateLeft(Node *&node) {
    //security checks...
    Node * rightSon = node->right;
    node->right = rightSon->left;
    rightSon->left = node;
    node = rightSon;
}

void AvlTree::rotateRight(Node *&node) {
    Node * leftSon = node->left;
    node->left = leftSon->right;
    leftSon->right = node;
    node = leftSon;
}

void AvlTree::fixTree(Node *&node, int direction) {
    //direction = 0 ==> sx else dx
    if(direction == 1)
    {
        //cerca il sottoalbero che crea lo sbilanciamento

        int hl = node->left != nullptr ? getNodeHeight(node->left->left) : -1;
        int hr = node->right != nullptr ? getNodeHeight(node->left->right) : -1;

        //caso SS
        if(hl > hr) {
            rotateRight(node);
        } else {
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    else if(direction == 0)
    {
        int hl = node->left != nullptr ? getNodeHeight(node->left->left) : -1;
        int hr = node->right != nullptr ? getNodeHeight(node->left->right) : -1;

        //caso DD
        if(hr > hl) {
            rotateLeft(node);
        } else {
            rotateRight(node->left);
            rotateLeft(node);
        }
    }

}

void AvlTree::insert(int info) {
    this->insertHelper(root, info);
}


void AvlTree::insertHelper(Node *&rootNode, int info)
{
    if(rootNode == nullptr)
    {
        Node *node = new Node(info, 0, nullptr, nullptr);
        rootNode = node;
    }
    else
    {
        if(info <= rootNode->info) {
            insertHelper(rootNode->left, info);
            rootNode->height = assignHeight(rootNode, rootNode->left, 0);
        }
        else {
            insertHelper(rootNode->right, info);
            rootNode->height = assignHeight(rootNode, rootNode->right, 0);
        }

        //calcola fattore di bilanciamento
        int hl = getNodeHeight(rootNode->left);
        int hr = getNodeHeight(rootNode->right);

        int balanceFactor = hl - hr;

        //sbilanciamento a sinitra
        if(balanceFactor == 2) {
            fixTree(rootNode, 1);
        }
        //sbilanciamento a destra
        else if(balanceFactor == -2) {
            fixTree(root, 0);
        }
    }
}

int AvlTree::getNodeHeight(Node *node) {
    return node == nullptr ? -1 : node->height;
}
//
// Created by weiss on 27/04/23.
//

#include "FstTree.h"
#include <iostream>

FstTree::FstTree(int rootKey) {
    root = nullptr;
    insertHelper(root, rootKey);
}

void FstTree::insert(int info) {
    insertHelper(root, info);
}

bool FstTree::search(int key) {
    return fogSearch(root, key);
}

void FstTree::remove(int key)
{
    removeHelper(root, key);
}

void FstTree::rotateRight(Node *&node) {
    if(node->left == nullptr) return;

    Node * leftSon = node->left;
    node->left = leftSon->right;
    leftSon->right = node;
    node = leftSon;
}

void FstTree::rotateLeft(Node *&node) {
    //security checks...
    if(node->right == nullptr) return;

    Node * rightSon = node->right;
    node->right = rightSon->left;
    rightSon->left = node;
    node = rightSon;
}

bool FstTree::fogSearch(Node *&node, int key) {
    if(node == nullptr) return false;

    else if(node->info == key) {
        return true;
    }
    else
    {
        if(key <= node->info) {
            bool res = fogSearch(node->left, key);
            rotateRight(node);
            return res;
        }

        else {
            bool res = fogSearch(node->right, key);
            rotateLeft(node);
            return res;
        }
    }
}

void FstTree::insertHelper(Node *&rootNode, int info)
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
            rotateRight(rootNode);
        }
        else {
            insertHelper(rootNode->right, info);
            rotateLeft(rootNode);
        }
    }
}

void FstTree::removeHelper(Node *&rootNode, int info)
{
    if(rootNode == nullptr) return;

    //se rootNode != nullptr, si cerca il nodo da cancellare
    if(info < rootNode->info) {
        removeHelper(rootNode->left, info);
        rotateRight(rootNode);
    }
    else if(info > rootNode->info) {
        removeHelper(rootNode->right, info);
        rotateLeft(rootNode);
    }

    //se viene trovato
    else
    {
        if(rootNode->left == nullptr)
        {
            Node *tmp = rootNode->right;
            delete rootNode;
            rootNode = tmp;
        }

        else if(rootNode->right == nullptr)
        {
            Node *tmp = rootNode->left;
            delete rootNode;
            rootNode = tmp;
        }

        else
        {
            //si cerca il minimo del sottoalbero destro
            Node *& minNode = minHelper(rootNode->right);

            //si copia il valore del minimo nel nodo da cancellare
            rootNode->info = minNode->info;

            //si cancella il minimo
            removeHelper(minNode, minNode->info);
        }
    }
}

FstTree::~FstTree() {
    deleteTree(root);
}

void FstTree::deleteTree(Node *&rootNode)
{
    if(rootNode != nullptr)
    {
        deleteTree(rootNode->left);
        deleteTree(rootNode->right);
        delete rootNode;
    }
}

void FstTree::inOrder() {
    inOrderHelper(root);
}

void FstTree::inOrderHelper(Node *root)
{
    if(root != nullptr)
    {
        inOrderHelper(root->left);
        std::cout << root->info << " ";
        inOrderHelper(root->right);
    }
}


Node *&FstTree::minHelper(Node *&rootNode) {
    if(rootNode == nullptr) {
        return rootNode;
    }
    else if(rootNode->left == nullptr) {
        return rootNode;
    }
    else return minHelper(rootNode->left);
}

//
// Created by Raffaele on 28/04/2023.
//
#pragma once

#include "SplayTree.h"
#include <iostream>

template <typename T>

SplayTree<T>::SplayTree() {
    root = nullptr;
}

template<typename T>
void SplayTree<T>::inOrder() {
    inOrderHelper(root);
    std::cout << std::endl;
}

template<typename T>
void SplayTree<T>::inOrderHelper(SplayNode<T> *tree)
{
    if(tree != nullptr)
    {
        inOrderHelper(tree->left);
        std::cout << tree->info << " ";
        inOrderHelper(tree->right);
    }
}

template<typename T>
void SplayTree<T>::climbInsert(const T &key) {
    SplayNode<T> *node = root;
    SplayNode<T> *prev = nullptr;

    while(node != nullptr) {
        prev = node;
        if(key <= node->info) {
            node = node->left;
        } else {
            node = node->right;
        }
    }


    node = new SplayNode<T>(key, nullptr, nullptr, prev);

    if(prev == nullptr)
        root = node;
    else if(prev->info < node->info)
        prev->right = node;
    else prev->left = node;

    climb(node);
}

template<typename T>
void SplayTree<T>::climb(SplayNode<T> *node) {
    //se node non è la radice
    while(node->parent != nullptr)
    {
        //casistica: zig
        if(node->parent->parent == nullptr)
        {
            //zig destro
            if(node->parent->right == node) {
                rotateLeft(node->parent);
            }
            else {
                rotateRight(node->parent);
            }
        }

        else
        {
            //zig-zig
            if(node->parent->parent->right == node->parent && node->parent->right == node) {
                rotateLeft(node->parent->parent);
                rotateLeft(node->parent);
            }
            else if(node->parent->parent->left == node->parent && node->parent->left == node) {
                rotateRight(node->parent->parent);
                rotateRight(node->parent);
            }
            //zig-zag
            else if(node->parent->parent->right == node->parent && node->parent->left == node) {
                rotateRight(node->parent);
                rotateLeft(node->parent);
            }

            else {
                rotateLeft(node->parent);
                rotateRight(node->parent);
            }
        }
    }
}

template<typename T>
void SplayTree<T>::rotateLeft(SplayNode<T> *node) {
    SplayNode<T> *rightSon = node->right;

    if (rightSon != nullptr)
    {
        node->right= rightSon->left;

        if (rightSon->left!= nullptr)
            rightSon->left->parent = node;

        rightSon->parent = node->parent;
    }

    if (node->parent == nullptr)
        root = rightSon;
    else if (node == node->parent->left)
        node->parent->left = rightSon;
    else
        node->parent->right = rightSon;
    if (rightSon != nullptr)
        rightSon->left = node;

    node->parent = rightSon;
}

template<typename T>
void SplayTree<T>::rotateRight(SplayNode<T> *node) {
    SplayNode<T> *leftSon = node->left;

    if (leftSon != nullptr)
    {
        node->left= leftSon->right;

        if (leftSon->right != nullptr)
            leftSon->right->parent = node;

        leftSon->parent = node->parent;
    }

    if (node->parent == nullptr)
        root = leftSon;
    else if (node == node->parent->left)
        node->parent->left = leftSon;
    else
        node->parent->right = leftSon;

    if (leftSon != nullptr)
        leftSon->right = node;

    node->parent = leftSon;
}

template<typename T>
void SplayTree<T>::deleteTree(SplayNode<T> *&rootNode) {
    if(rootNode != nullptr)
    {
        deleteTree(rootNode->left);
        deleteTree(rootNode->right);
        delete rootNode;
    }
}
//
// Created by weiss on 27/04/23.
//

#pragma once
#include "FstTree.h"
#include <iostream>

template <class T>
void FstTree<T>::insert(T info) {
    insertHelper(root, info);
}

template <class T>
bool FstTree<T>::search(T key) {
    return fogSearch(root, key);
}

template <class T>
void FstTree<T>::remove(T key)
{
    removeHelper(root, key);
}

template <class T>
void FstTree<T>::rotateRight(Node<T> *&node) {
    if(node->left == nullptr) return;

    Node<T> * leftSon = node->left;
    node->left = leftSon->right;
    leftSon->right = node;
    node = leftSon;
}

template <class T>
void FstTree<T>::rotateLeft(Node<T> *&node) {
    //security checks...
    if(node->right == nullptr) return;

    Node<T> * rightSon = node->right;
    node->right = rightSon->left;
    rightSon->left = node;
    node = rightSon;
}

template <class T>
bool FstTree<T>::fogSearch(Node<T> *&node, T key) {
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

template <class T>
void FstTree<T>::insertHelper(Node<T> *&rootNode, T info)
{
    if(rootNode == nullptr)
    {
        Node<T> *node = new Node<T>(info, 0, nullptr, nullptr);
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

template <class T>
void FstTree<T>::removeHelper(Node<T> *&rootNode, T info)
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
            Node<T> *tmp = rootNode->right;
            delete rootNode;
            rootNode = tmp;
        }

        else if(rootNode->right == nullptr)
        {
            Node<T> *tmp = rootNode->left;
            delete rootNode;
            rootNode = tmp;
        }

        else
        {
            //si cerca il minimo del sottoalbero destro
            Node<T> *& minNode = minHelper(rootNode->right);

            //si copia il valore del minimo nel nodo da cancellare
            rootNode->info = minNode->info;

            //si cancella il minimo
            removeHelper(minNode, minNode->info);
        }
    }
}


template <class T>
void FstTree<T>::deleteTree(Node<T> *&rootNode)
{
    if(rootNode != nullptr)
    {
        deleteTree(rootNode->left);
        deleteTree(rootNode->right);
        delete rootNode;
    }
}

template <class T>
void FstTree<T>::inOrder() {
    inOrderHelper(root);
}

template <class T>
void FstTree<T>::inOrderHelper(Node<T> *root)
{
    if(root != nullptr)
    {
        inOrderHelper(root->left);
        std::cout << root->info << " ";
        inOrderHelper(root->right);
    }
}


template <class T>
Node<T> *&FstTree<T>::minHelper(Node<T> *&rootNode) {
    if(rootNode == nullptr) {
        return rootNode;
    }
    else if(rootNode->left == nullptr) {
        return rootNode;
    }
    else return minHelper(rootNode->left);
}
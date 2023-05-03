//
// Created by Raffaele on 24/04/2023.
//

#pragma once

#include "AvlTree.h"

template <class T>
AvlTree<T>::AvlTree(T rootKey) : BstTree<T>(rootKey) {

}

template <class T>
AvlTree<T>::AvlTree(const std::vector<T> &keys) : BstTree<T>(keys) {
    this->root = nullptr;
    for(int key : keys) {
        AvlTree::insertHelper(this->root, key);
    }
}

template <class T>
void AvlTree<T>::insert(T info) {
    this->insertHelper(this->root, info);
}

template <class T>
void AvlTree<T>::insertHelper(Node<T> *&rootNode, int info)
{
    if(rootNode == nullptr)
    {
        auto *node = new Node<T>(info, 0, nullptr, nullptr);
        rootNode = node;
    }
    else
    {
        if(info <= rootNode->info) {
            this->insertHelper(rootNode->left, info);
            rootNode->height = this->assignHeight(rootNode);
        }
        else {
            this->insertHelper(rootNode->right, info);
            rootNode->height = this->assignHeight(rootNode);
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
            fixTree(rootNode, 0);
        }
    }
}
template <class T>
void AvlTree<T>::remove(T key) {
    this->removeHelper(this->root, key);
}

template <class T>
void AvlTree<T>::removeHelper(Node<T> *&rootNode, int info)
{
    //caso 1: l'elemento non è stato trovato
    if(rootNode == nullptr) return;

    //se rootNode != nullptr, si cerca il nodo da cancellare
    if(info < rootNode->info) {
        this->removeHelper(rootNode->left, info);
        rootNode->height = this->assignHeight(rootNode);
    }
    else if(info > rootNode->info) {
        this->removeHelper(rootNode->right, info);
        rootNode->height = this->assignHeight(rootNode);
    }

    //se viene trovato
    else
    {
        //caso 1: il nodo da cancellare è una foglia
        //caso 2: il nodo da cancellare ha un figlio
        //..destro
        if(rootNode->left == nullptr)
        {
            Node<T> *tmp = rootNode->right;
            delete rootNode;
            rootNode = tmp;
        }

        //.. sinistro
        else if(rootNode->right == nullptr)
        {
            Node<T> *tmp = rootNode->left;
            delete rootNode;
            rootNode = tmp;
        }

        //caso 3: il nodo da cancellare ha 3 figli
        else
        {
            //si cerca il minimo del sottoalbero destro
            Node<T> *& minNode = this->minHelper(rootNode->right);

            //si copia il valore del minimo nel nodo da cancellare
            rootNode->info = minNode->info;

            //si cancella il minimo
            this->removeHelper(minNode, minNode->info);
        }
    }

    if(rootNode != nullptr)
    {
        int hl = getNodeHeight(rootNode->left);
        int hr = getNodeHeight(rootNode->right);

        int balanceFactor = hl - hr;

        //sbilanciamento a sinitra
        if (balanceFactor == 2) {
            fixTree(rootNode, 1);
        }
            //sbilanciamento a destra
        else if (balanceFactor == -2) {
            fixTree(rootNode, 0);
        }
    }
}

template <class T>
void AvlTree<T>::rotateLeft(Node<T> *&node) {
    //security checks...
    Node<T> * rightSon = node->right;
    node->right = rightSon->left;
    rightSon->left = node;
    node = rightSon;

    //aggiorna le altezze per "v"
    node->left->height = this->assignHeight(node->left);
    //.. e per u
    node->height = this->assignHeight(node);
}
template <class T>
void AvlTree<T>::rotateRight(Node<T> *&node) {

    //aggiorna le altezze
    Node<T> * leftSon = node->left;
    node->left = leftSon->right;
    leftSon->right = node;
    node = leftSon;

    //aggiorna le altezze per "v"
    node->right->height = this->assignHeight(node->right);

    //.. e per u
    node->height = this->assignHeight(node);

}

template <class T>
void AvlTree<T>::fixTree(Node<T> *&node, int direction) {

    //sbilanciamento a sx
    if(direction == 1)
    {
        //cerca il sottoalbero che crea lo sbilanciamento
        int hl = node->left != nullptr ? getNodeHeight(node->left->left) : -1;
        int hr = node->left != nullptr ? getNodeHeight(node->left->right) : -1;

        //caso SS
        if(hl > hr) {
            rotateRight(node);
        } else {
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    //sbilanciamento a  destra
    else {
        int hl = node->right != nullptr ? getNodeHeight(node->right->left) : -1;
        int hr = node->right != nullptr ? getNodeHeight(node->right->right) : -1;

        //caso DD
        if (hr > hl) {
            rotateLeft(node);
        } else {
            rotateRight(node->right);
            rotateLeft(node);
        }
    }

}

template <class T>
int AvlTree<T>::getNodeHeight(Node<T> *node) {
    return node == nullptr ? -1 : node->height;
}



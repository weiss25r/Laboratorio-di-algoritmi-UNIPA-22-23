//
// Created by Raffaele on 21/04/2023.
//
#pragma once
#include "BstTree.h"

#include <climits>


template<class T>
BstTree<T>::BstTree(T rootKey) {
    root = new Node<T>(rootKey, 0, nullptr, nullptr);
}

template<class T>
BstTree<T>::BstTree(const std::vector<T> &keys) {
    root = nullptr;
    for(int key : keys) {
        BstTree<T>::insertHelper(root, key);
    }
}

template<class T>
BstTree<T>::BstTree(const BstTree &bst) {
    root = nullptr;
    copyHelper(root, bst.root);
}

template<class T>
BstTree<T>::~BstTree() {
    deleteTree(root);
}

template<class T>
//getter for height
int BstTree<T>::getHeight() const {
    return this->root != nullptr ? root->height : -1;
}

template<class T>
//dictionary operations
void BstTree<T>::insert(int info) {
    insertHelper(root, info);
}

template<class T>
bool BstTree<T>::search(int key) const{
    return searchHelper(root, key);
}

template<class T>
void BstTree<T>::remove(int key) {
    if(searchHelper(root, key))
        removeHelper(root, key);
}

template<class T>
//traversals
void BstTree<T>::preOrder() const {
    preOrderHelper(root);
}

template<class T>
void BstTree<T>::postOrder() const{
    postOrderHelper(root);
}

template<class T>
void BstTree<T>::inOrder() const{
    inOrderHelper(root);
}

template<class T>
//max and min
T BstTree<T>::max() {
    if(root != nullptr) {
        Node<T> *maxNode = maxHelper(root);
        return maxNode->info;
    }
    else return nullptr;
}

template<class T>
T BstTree<T>::min() {
    if(root != nullptr) {
        Node<T> *minNode = minHelper(root);
        return minNode->info;
    }
    else return nullptr;
}

template<class T>
//"helper" methods
void BstTree<T>::insertHelper(Node<T> *&rootNode, int info)
{
    if(rootNode == nullptr)
    {
        auto *node = new Node<T>(info, 0, nullptr, nullptr);
        rootNode = node;
    }
    else
    {
        if(info <= rootNode->info) {
            insertHelper(rootNode->left, info);
            rootNode->height = assignHeight(rootNode);
        }
        else {
            insertHelper(rootNode->right, info);
            rootNode->height = assignHeight(rootNode);
        }
    }
}

template<class T>
bool BstTree<T>::searchHelper(Node<T> *rootNode, int info) const{
    if(rootNode == nullptr) {
        return false;
    }
    else if(rootNode->info == info) {
        return true;
    }
    else {
        if(info <= rootNode->info) {
            return searchHelper(rootNode->left, info);
        }
        else {
            return searchHelper(rootNode->right, info);
        }
    }
}

template<class T>
void BstTree<T>::removeHelper(Node<T> *&rootNode, int info)
{
    //caso 1: l'elemento non è stato trovato
    if(rootNode == nullptr) return;

    //se rootNode != nullptr, si cerca il nodo da cancellare
    if(info < rootNode->info) {
        removeHelper(rootNode->left, info);
        rootNode->height = assignHeight(rootNode);
    }
    else if(info > rootNode->info) {
        removeHelper(rootNode->right, info);
        rootNode->height = assignHeight(rootNode);
    }

        //se viene trovato
    else
    {
        //caso 1: il nodo da cancellare è una foglia oppure ha un figlio

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

            //caso 2: il nodo da cancellare ha 2 figli
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

template<class T>
Node<T> *BstTree<T>::maxHelper(Node<T> *rootNode) const {
    if(rootNode == nullptr) {
        return nullptr;
    }
    else if(rootNode->right == nullptr && rootNode->left == nullptr) {
        return rootNode;
    }
    else return maxHelper(rootNode->right);
}

template<class T>
Node<T> *&BstTree<T>::minHelper(Node<T> *&rootNode) {
    if(rootNode == nullptr) {
        return rootNode;
    }
    else if(rootNode->left == nullptr) {
        return rootNode;
    }
    else return minHelper(rootNode->left);
}

template<class T>
void BstTree<T>::inOrderHelper(Node<T> *rootNode) const{
    if(rootNode != nullptr)
    {
        inOrderHelper(rootNode->left);
        std::cout << rootNode->info << " ";
        inOrderHelper(rootNode->right);
    }
}

template<class T>
void BstTree<T>::preOrderHelper(Node<T> *rootNode) const
{
    if(rootNode != nullptr)
    {
        std::cout << rootNode->info << " ";
        preOrderHelper(rootNode->left);
        preOrderHelper(rootNode->right);
    }
}

template<class T>
void BstTree<T>::postOrderHelper(Node<T> *rootNode) const
{
    if(rootNode != nullptr)
    {
        postOrderHelper(rootNode->left);
        postOrderHelper(rootNode->right);
        std::cout << rootNode->info << " ";
    }
}


template<class T>
//free the memory in destructor
void BstTree<T>::deleteTree(Node<T> *&rootNode)
{
    if(rootNode != nullptr)
    {
        deleteTree(rootNode->left);
        deleteTree(rootNode->right);
        delete rootNode;
    }
}

template<class T>
int BstTree<T>::assignHeight(Node<T> *node) {
    int leftHeight = node->left != nullptr ? node->left->height : -1 ;
    int rightHeight = node->right != nullptr ? node->right->height : -1;

    return 1 + std::max(leftHeight, rightHeight);
}

template<class T>

void BstTree<T>::copyHelper(Node<T> *&rootOne, Node<T> *rootTwo)
{
    if(rootTwo != nullptr)
    {
        //visita in PRE-ordine
        //copia la radice
        rootOne = new Node<T>(rootTwo->info, rootTwo->height, nullptr, nullptr);

        //copia il sottoalbero sinistro
        copyHelper(rootOne->left, rootTwo->left);
        copyHelper(rootOne->right, rootTwo->right);
    }
}

template<class T>
//operators
BstTree<T>& BstTree<T>::operator=(const BstTree &bst) {
    if(this != &bst)
    {
        deleteTree(root);
        root = nullptr;
        copyHelper(root, bst.root);
    }
    return *this;
}


template<class T>
std::ostream &operator<<(std::ostream &os, const BstTree<T> &bst) {

    if(!bst.isEmpty()) {
        os << "In order traversal: ";
        bst.inOrder();
        os << std::endl;
        os << "Pre order traversal: ";
        bst.preOrder();
        os << std::endl;

        os << "Post order traversal: ";
        bst.postOrder();
        os << std::endl;

        os << "Tree height: " << bst.getHeight() << std::endl;
        os << std::endl;
    }

    else os << "Tree is empty";

    return os;
}






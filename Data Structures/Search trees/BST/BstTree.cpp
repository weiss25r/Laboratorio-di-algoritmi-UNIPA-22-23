//
// Created by Raffaele on 21/04/2023.
//

#include "BstTree.h"

#include <iostream>
#include <climits>
BstTree::BstTree(int rootKey) {
    root = new Node(rootKey, 0, nullptr, nullptr);
}

BstTree::BstTree(const std::vector<int> &keys) {
    root = nullptr;
    for(int key : keys) {
        BstTree::insertHelper(root, key);
    }
}

BstTree::BstTree(const BstTree &bst) {
    root = nullptr;
    copyHelper(root, bst.root);
}

BstTree::~BstTree() {
    deleteTree(root);
}

//getter for height
int BstTree::getHeight() const {
    return this->root != nullptr ? root->height : -1;
}

//dictionary operations
void BstTree::insert(int info) {
    insertHelper(root, info);
}

bool BstTree::search(int key) const{
    return searchHelper(root, key);
}

void BstTree::remove(int key) {
    if(searchHelper(root, key))
        removeHelper(root, key);
}

//traversals
void BstTree::preOrder() const {
    preOrderHelper(root);
}

void BstTree::postOrder() const{
    postOrderHelper(root);
}

void BstTree::inOrder() const{
    inOrderHelper(root);
}

//max and min
int BstTree::max() {
    if(root != nullptr) {
        Node *maxNode = maxHelper(root);
        return maxNode->info;
    }
    else return INT_MAX;
}

int BstTree::min() {
    if(root != nullptr) {
        Node *minNode = minHelper(root);
        return minNode->info;
    }
    else return INT_MIN;
}

//"helper" methods
void BstTree::insertHelper(Node *&rootNode, int info)
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
            rootNode->height = assignHeight(rootNode);
        }
        else {
            insertHelper(rootNode->right, info);
            rootNode->height = assignHeight(rootNode);
        }
    }
}

bool BstTree::searchHelper(Node *rootNode, int info) const{
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

void BstTree::removeHelper(Node *&rootNode, int info)
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
            Node *tmp = rootNode->right;
            delete rootNode;
            rootNode = tmp;
        }

        //.. sinistro
        else if(rootNode->right == nullptr)
        {
            Node *tmp = rootNode->left;
            delete rootNode;
            rootNode = tmp;
        }

        //caso 2: il nodo da cancellare ha 2 figli
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

Node *BstTree::maxHelper(Node *rootNode) const {
    if(rootNode == nullptr) {
        return nullptr;
    }
    else if(rootNode->right == nullptr && rootNode->left == nullptr) {
        return rootNode;
    }
    else return maxHelper(rootNode->right);
}

Node *&BstTree::minHelper(Node *&rootNode) {
    if(rootNode == nullptr) {
        return rootNode;
    }
    else if(rootNode->left == nullptr) {
        return rootNode;
    }
    else return minHelper(rootNode->left);
}

void BstTree::inOrderHelper(Node *rootNode) const{
    if(rootNode != nullptr)
    {
        inOrderHelper(rootNode->left);
        std::cout << rootNode->info << " ";
        inOrderHelper(rootNode->right);
    }
}

void BstTree::preOrderHelper(Node *rootNode) const
{
    if(rootNode != nullptr)
    {
        std::cout << rootNode->info << " ";
        preOrderHelper(rootNode->left);
        preOrderHelper(rootNode->right);
    }
}

void BstTree::postOrderHelper(Node *rootNode) const
{
    if(rootNode != nullptr)
    {
        postOrderHelper(rootNode->left);
        postOrderHelper(rootNode->right);
        std::cout << rootNode->info << " ";
    }
}

//free the memory in destructor
void BstTree::deleteTree(Node *&rootNode)
{
    if(rootNode != nullptr)
    {
        deleteTree(rootNode->left);
        deleteTree(rootNode->right);
        delete rootNode;
    }
}

int BstTree::assignHeight(Node *node) {
    int leftHeight = node->left != nullptr ? node->left->height : -1 ;
    int rightHeight = node->right != nullptr ? node->right->height : -1;

    return 1 + std::max(leftHeight, rightHeight);
}


void BstTree::copyHelper(Node *&rootOne, Node *rootTwo)
{
    if(rootTwo != nullptr)
    {
        //visita in PRE-ordine
        //copia la radice
        rootOne = new Node(rootTwo->info, rootTwo->height, nullptr, nullptr);

        //copia il sottoalbero sinistro
        copyHelper(rootOne->left, rootTwo->left);
        copyHelper(rootOne->right, rootTwo->right);
    }
}

//operators
BstTree &BstTree::operator=(const BstTree &bst) {
    if(this != &bst)
    {
        deleteTree(root);
        root = nullptr;
        copyHelper(root, bst.root);
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const BstTree &bst) {

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






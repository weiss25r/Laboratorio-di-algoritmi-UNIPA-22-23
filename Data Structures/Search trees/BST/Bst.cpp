//
// Created by Raffaele on 21/04/2023.
//

#include "Bst.h"

#include <iostream>

Bst::Bst(int rootKey) {
    root = new Node(rootKey, 0, nullptr, nullptr);
}

Bst::Bst(const std::vector<int> &keys) {
    root = nullptr;
    for(int key : keys) {
        insertHelper(root, key);
    }
}

Bst::Bst(const Bst &bst) {
    root = nullptr;
    copyHelper(root, bst.root);
}

Bst::~Bst() {
    deleteTree(root);
}

//getter for heigth
int Bst::getHeigth() const {
    return this->root != nullptr ? root->heigth : -1;
}

//dictionary operations
void Bst::insert(int info) {
    insertHelper(root, info);
}

bool Bst::search(int key) const{
    return searchHelper(root, key);
}

void Bst::remove(int key) {
    if(searchHelper(root, key))
        removeHelper(root, key);
}

//visits
void Bst::preOrder() const {
    preOrderHelper(root);
}

void Bst::postOrder() const{
    postOrderHelper(root);
}

void Bst::inOrder() const{
    inOrderHelper(root);
}

//max and min
int Bst::max() {
    Node *max = maxHelper(root);
    return max->info;
}

int Bst::min() {
    Node *min = minHelper(root);
    return min->info;
}

//"helper" methods
void Bst::insertHelper(Node *&rootNode, int info)
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
            rootNode->heigth = assignHeigth(rootNode, rootNode->left, 0);
        }
        else {
            insertHelper(rootNode->right, info);
            rootNode->heigth = assignHeigth(rootNode, rootNode->right, 0);
        }
    }
}

bool Bst::searchHelper(Node *root, int info) const{
    if(root == nullptr) {
        return false;
    }
    else if(root->info == info) {
        return true;
    }
    else {
        if(info <= root->info) {
            return searchHelper(root->left, info);
        }
        else {
            return searchHelper(root->right, info);
        }
    }
}

void Bst::inOrderHelper(Node *rootNode) const{
    if(rootNode != nullptr)
    {
        inOrderHelper(rootNode->left);
        std::cout << rootNode->info << " ";
        inOrderHelper(rootNode->right);
    }
}

void Bst::preOrderHelper(Node *rootNode) const
{
    if(rootNode != nullptr)
    {
        std::cout << rootNode->info << " ";
        preOrderHelper(rootNode->left);
        preOrderHelper(rootNode->right);
    }
}

void Bst::postOrderHelper(Node *rootNode) const
{
    if(rootNode != nullptr)
    {
        postOrderHelper(rootNode->left);
        postOrderHelper(rootNode->right);
        std::cout << rootNode->info << " ";
    }
}

void Bst::removeHelper(Node *&rootNode, int info)
{
    //caso 1: l'elemento non è stato trovato
    if(rootNode == nullptr) return;

    //se rootNode != nullptr, si cerca il nodo da cancellare
    if(info < rootNode->info) {
        removeHelper(rootNode->left, info);
        rootNode->heigth = assignHeigth(rootNode, rootNode->right, 1);
    }
    else if(info > rootNode->info) {
        removeHelper(rootNode->right, info);
        rootNode->heigth = assignHeigth(rootNode, rootNode->left, 1);
    }

    //se viene trovato
    else
    {
        //caso 1: il nodo da cancellare è una foglia
        if(rootNode->left == nullptr && rootNode->right == nullptr)
        {
            delete rootNode;
            rootNode = nullptr;
        }

        //caso 2: il nodo da cancellare ha un figlio

        //..destro
        else if(rootNode->right != nullptr && rootNode->left == nullptr)
        {
            Node *tmp = rootNode->right;
            delete rootNode;
            rootNode = tmp;
        }

        //.. sinistro
        else if(rootNode->left != nullptr && rootNode->right == nullptr)
        {
            Node *tmp = rootNode->left;
            delete rootNode;
            rootNode = tmp;
        }

        //caso 3: il nodo da cancellare ha 3 figli
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

Node *Bst::maxHelper(Node *rootNode) const {
    if(rootNode == nullptr) {
        return nullptr;
    }
    else if(rootNode->right == nullptr && rootNode->left == nullptr) {
        return rootNode;
    }
    else return maxHelper(rootNode->right);
}

Node *&Bst::minHelper(Node *&rootNode) {
    if(rootNode == nullptr) {
        return rootNode;
    }
    else if(rootNode->left == nullptr) {
        return rootNode;
    }
    else return minHelper(rootNode->right);
}

//free the memory in destructor
void Bst::deleteTree(Node *&rootNode)
{
    if(rootNode != nullptr)
    {
        deleteTree(rootNode->left);
        deleteTree(rootNode->right);
        delete rootNode;
    }
}

int Bst::assignHeigth(Node *nodeOne, Node *nodeTwo, int mode) {
    if(nodeTwo == nullptr) {
        return nodeOne->heigth - 1;
    }
    //mode == 0: insertion
    else if(mode == 0) {
        int newHeigth = nodeTwo->heigth + 1;
        return newHeigth > nodeOne->heigth ? newHeigth : nodeOne->heigth;
    }
    //mode == 1: insertion
    else {
        int h1 = nodeOne->heigth-1;
        int h2 = nodeTwo->heigth+1;
        return h1 > h2 ? h1 : h2;
    }
}


void Bst::copyHelper(Node *&rootOne, Node *rootTwo)
{
    if(rootTwo != nullptr)
    {
        //visita in PRE-ordine
        //copia la radice
        rootOne = new Node(rootTwo->info, rootTwo->heigth, nullptr, nullptr);

        //copia il sottoalbero sinistro
        copyHelper(rootOne->left, rootTwo->left);
        copyHelper(rootOne->right, rootTwo->right);
    }
}

//operators
Bst &Bst::operator=(const Bst &bst) {
    if(this != &bst)
    {
        deleteTree(root);
        root = nullptr;
        copyHelper(root, bst.root);
    }
    return *this;
}
std::ostream &operator<<(std::ostream &os, const Bst &bst) {

    os << "In order traversal: ";
    bst.inOrder();
    os << std::endl;
    os << "Pre order traversal: ";
    bst.preOrder();
    os << std::endl;

    os << "Post order traversal: ";
    bst.postOrder();
    os << std::endl;

    os << "Tree heigth: " << bst.root->heigth << std::endl;
    os << std::endl;
    return os;
}






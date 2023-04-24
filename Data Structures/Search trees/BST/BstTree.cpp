//
// Created by Raffaele on 21/04/2023.
//

#include "BstTree.h"

#include <iostream>

BstTree::BstTree(int rootKey) {
    root = new Node(rootKey, 0, nullptr, nullptr);
}

BstTree::BstTree(const std::vector<int> &keys) {
    root = nullptr;
    for(int key : keys) {
        insertHelper(root, key);
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

//visits
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
    Node *max = maxHelper(root);
    return max->info;
}

int BstTree::min() {
    Node *min = minHelper(root);
    return min->info;
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
            rootNode->height = assignHeight(rootNode, rootNode->left, 0);
        }
        else {
            insertHelper(rootNode->right, info);
            rootNode->height = assignHeight(rootNode, rootNode->right, 0);
        }
    }
}

bool BstTree::searchHelper(Node *root, int info) const{
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

void BstTree::removeHelper(Node *&rootNode, int info)
{
    //caso 1: l'elemento non è stato trovato
    if(rootNode == nullptr) return;

    //se rootNode != nullptr, si cerca il nodo da cancellare
    if(info < rootNode->info) {
        removeHelper(rootNode->left, info);
        rootNode->height = assignHeight(rootNode, rootNode->right, 1);
    }
    else if(info > rootNode->info) {
        removeHelper(rootNode->right, info);
        rootNode->height = assignHeight(rootNode, rootNode->left, 1);
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

int BstTree::assignHeight(Node *nodeOne, Node *nodeTwo, int mode) {
    if(nodeTwo == nullptr) {
        return nodeOne->height - 1;
    }
    //mode == 0: insertion
    else if(mode == 0) {
        int newheight = nodeTwo->height + 1;
        return newheight > nodeOne->height ? newheight : nodeOne->height;
    }
    //mode == 1: insertion
    else {
        int h1 = nodeOne->height-1;
        int h2 = nodeTwo->height+1;
        return h1 > h2 ? h1 : h2;
    }
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

    os << "In order traversal: ";
    bst.inOrder();
    os << std::endl;
    os << "Pre order traversal: ";
    bst.preOrder();
    os << std::endl;

    os << "Post order traversal: ";
    bst.postOrder();
    os << std::endl;

    os << "Tree height: " << bst.root->height << std::endl;
    os << std::endl;
    return os;
}






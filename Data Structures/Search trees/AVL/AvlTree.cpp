//
// Created by Raffaele on 24/04/2023.
//

#include "AvlTree.h"

AvlTree::AvlTree(int rootKey) : BstTree(rootKey) {}

AvlTree::AvlTree(const std::vector<int> &keys) : BstTree(keys) {
    root = nullptr;
    for(int key : keys) {
        AvlTree::insertHelper(root, key);
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
            rootNode->height = assignHeight(rootNode);
        }
        else {
            insertHelper(rootNode->right, info);
            rootNode->height = assignHeight(rootNode);
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

void AvlTree::remove(int key) {
    removeHelper(root, key);
}

void AvlTree::removeHelper(Node *&rootNode, int info)
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
        //caso 1: il nodo da cancellare è una foglia
        //caso 2: il nodo da cancellare ha un figlio
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

void AvlTree::rotateLeft(Node *&node) {
    //security checks...
    Node * rightSon = node->right;
    node->right = rightSon->left;
    rightSon->left = node;
    node = rightSon;

    //aggiorna le altezze per "v"
    node->left->height = assignHeight(node->left);
    //.. e per u
    node->height = assignHeight(node);
}

void AvlTree::rotateRight(Node *&node) {

    //aggiorna le altezze
    Node * leftSon = node->left;
    node->left = leftSon->right;
    leftSon->right = node;
    node = leftSon;

    //aggiorna le altezze per "v"
    node->right->height = assignHeight(node->right);

    //.. e per u
    node->height = assignHeight(node);

}

void AvlTree::fixTree(Node *&node, int direction) {

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

int AvlTree::getNodeHeight(Node *node) {
    return node == nullptr ? -1 : node->height;
}




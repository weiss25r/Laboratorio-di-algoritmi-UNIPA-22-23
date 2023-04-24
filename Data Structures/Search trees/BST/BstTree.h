//
// Created by Raffaele on 21/04/2023.
//

#ifndef BST_BSTTREE_H
#define BST_BSTTREE_H

#include <vector>
#include <ostream>

struct Node {
    int info;
    int height;
    Node *left;
    Node *right;

    Node(int info, int height, Node *left, Node *right) : info(info), height(height), left(left), right(right) {}
};

class BstTree {

public:
    explicit BstTree(int rootKey);
    explicit BstTree(const std::vector<int> &keys);
    BstTree(const BstTree &bst);
    virtual void insert(int info);
    bool search(int key) const;
    virtual void remove(int key);
    int max();
    int min();
    int getHeight() const;
    void inOrder() const;
    void preOrder() const;
    void postOrder() const;
    BstTree& operator=(const BstTree& bst);
    ~BstTree();

    friend std::ostream &operator<<(std::ostream &os, const BstTree &bst);

protected:
    Node *root;
    virtual void insertHelper(Node* &rootNode, int info);
    virtual void removeHelper(Node *&rootNode, int info);
    bool searchHelper(Node *rootNode, int info) const;
    Node *maxHelper(Node *rootNode) const;
    Node *&minHelper(Node *&rootNode);
    void inOrderHelper(Node * rootNode) const;
    void preOrderHelper(Node * rootNode) const;
    void postOrderHelper(Node * rootNode) const;
    void deleteTree(Node *&rootNode);
    int assignHeight(Node *nodeOne, Node *nodeTwo, int mode);
    void copyHelper(Node *&rootOne, Node *rootTwo);
};



#endif //BST_BSTTREE_H

//
// Created by Raffaele on 21/04/2023.
//

#ifndef BST_BST_H
#define BST_BST_H

#include <vector>
#include <ostream>

struct Node {
    int info;
    int height;
    Node *left;
    Node *right;

    Node(int info, int height, Node *left, Node *right) : info(info), height(height), left(left), right(right) {}
};

class Bst {

public:
    //add copy constructor, = and ==
    explicit Bst(int rootKey);
    explicit Bst(const std::vector<int> &keys);
    Bst( const Bst &bst);
    void insert(int info);
    bool search(int key) const;
    void remove(int key);
    int max();
    int min();
    int getheight() const;
    void inOrder() const;
    void preOrder() const;
    void postOrder() const;
    Bst& operator=(const Bst& bst);
    ~Bst();

    friend std::ostream &operator<<(std::ostream &os, const Bst &bst);

private:
    Node *root;
    void insertHelper(Node* &rootNode, int info);
    void removeHelper(Node *&rootNode, int info);
    bool searchHelper(Node *rootNode, int info) const;
    Node *maxHelper(Node *rootNode) const;
    Node *&minHelper(Node *&rootNode);
    void inOrderHelper(Node * rootNode) const;
    void preOrderHelper(Node * rootNode) const;
    void postOrderHelper(Node * rootNode) const;
    void deleteTree(Node *&rootNode);
    int assignheight(Node *nodeOne, Node *nodeTwo, int mode);
    void copyHelper(Node *&rootOne, Node *rootTwo);
};



#endif //BST_BST_H

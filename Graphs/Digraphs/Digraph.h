//
// Created by weiss on 11/05/23.
//

#ifndef GRAPHS_DIGRAPH_H
#define GRAPHS_DIGRAPH_H

#include <iostream>
#include <vector>

using std::vector;
using std::ifstream;

struct Node {
    int info;
    Node *next;

    Node(int info, Node *next) : info(info), next(next) {};

};

class Digraph {
public:
    explicit Digraph(int v);
    explicit Digraph(ifstream inputFile);
    virtual ~Digraph();

    void insertEdge(int v, int u);
    int size() const;
    const vector<Node*>& getAdjList() const;
    Digraph reverse();
    vector<int> topologicalSort();
    void printGraph();
private:
    int numV, numE;
    vector<Node*> adj;
    void freeList(Node *list);
};

#endif //GRAPHS_DIGRAPH_H

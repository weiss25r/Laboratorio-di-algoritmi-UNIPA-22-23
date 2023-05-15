//
// Created by Raffaele on 11/05/23.
//

#ifndef GRAPHS_DIGRAPH_H
#define GRAPHS_DIGRAPH_H

#include <iostream>
#include <vector>
#include <list>

using std::vector;
using std::ifstream;
using std::list;

class Digraph {
public:
    explicit Digraph(int v);
    explicit Digraph(ifstream inputFile);

    int getNumV() const;
    int getNumE() const;
    const vector<list<int>> &getAdj() const;

    void insertEdge(int v, int w);
    bool pointsTo(int v, int w);
    const list<int> & neighbours(int v);
    void printGraph();

    Digraph reverse();
    vector<int> topologicalSort();

private:
    int numV, numE;
    vector<list<int>> adj;
};

#endif //GRAPHS_DIGRAPH_H

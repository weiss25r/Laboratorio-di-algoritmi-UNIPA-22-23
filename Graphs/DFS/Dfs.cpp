//
// Created by Raffaele on 13/05/2023.
//

#include "Dfs.h"
#include <algorithm>

Dfs::Dfs(const Digraph& g) : graph(g), marked(g.getNumV()) { }

void Dfs::dfs(int source)
{
    if(graph.getNumV() >= 0 && source < graph.getNumV())
    {
        preOrder = std::queue<int>();
        postOrder = std::queue<int>();
        revPostOrder = std::stack<int>();

        dfsHelper(source);
        std::fill(marked.begin(), marked.end(), false);
    }
    else std::cout << "Il vertice specificato non esiste nel grafo" << std::endl;
}

void Dfs::dfsHelper(int source) {
    marked[source] = true;
    auto edges = graph.getAdj().at(source);

    //pre-order
    preOrder.push(source);

    for(const int &vertex : edges) {
        if(!marked[vertex]) {
            dfsHelper(vertex);
        }
    }

    postOrder.push(source);
    revPostOrder.push(source);
}

const std::queue<int> &Dfs::getPreOrderDfs() {
    return preOrder;
}

const std::queue<int> &Dfs::getPostOrder() {
    return postOrder;
}

const std::stack<int> &Dfs::getRevPostOrderDfs() {
    return revPostOrder;
}



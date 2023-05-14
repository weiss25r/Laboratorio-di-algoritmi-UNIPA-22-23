//
// Created by Raffaele on 13/05/2023.
//

#include "Dfs.h"
#include <algorithm>

Dfs::Dfs(const Digraph& g) : graph(g), marked(g.size()) { }

void Dfs::dfs(int source) {
    if(source <= graph.size())
    {
        dfsHelper(source);
        std::fill(marked.begin(), marked.end(), false);
    }
    else std::cout << "Il vertice specificato non esiste nel grafo" << std::endl;
}

void Dfs::dfsHelper(int source) {
    marked[source] = true;
    Node *edges = graph.getAdjList().at(source);

    //pre-order
    preOrder.push(source);

    while(edges != nullptr) {
        if(!marked[edges->info]) {
            dfsHelper(edges->info);
        }
        edges = edges->next;
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



//
// Created by Raffaele on 13/05/2023.
//

#ifndef GRAPHS_DFS_H
#define GRAPHS_DFS_H

#include <queue>
#include <stack>
#include <vector>
#include "../Digraphs/Digraph.h"

class Dfs {
public:
    explicit Dfs(const Digraph &g);
    void dfs(int source);
    const std::queue<int> &getPreOrderDfs();
    const std::queue<int> &getPostOrder();
    const std::stack<int> &getRevPostOrderDfs();

private:
    const Digraph &graph;
    vector<bool> marked;
    std::queue<int> preOrder;
    std::queue<int> postOrder;
    std::stack<int> revPostOrder;

    void dfsHelper(int source);
};


#endif //GRAPHS_DFS_H

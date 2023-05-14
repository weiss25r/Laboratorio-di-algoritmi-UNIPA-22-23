#include <iostream>
#include <fstream>
#include "Digraphs/Digraph.h"
#include "DFS/Dfs.h"

using namespace std;

int main() {

    Digraph g(ifstream("Test files/sedg.txt"));
    Digraph topSort(ifstream("Test files/tsort.txt"));

    Dfs dfs(g);
    dfs.dfs(0);

    auto preOrder = dfs.getPreOrderDfs();
    auto postOrder = dfs.getPostOrder();
    auto revPostOrder = dfs.getRevPostOrderDfs();

    cout << "Pre order DFS of graph g" << endl;
    while(!preOrder.empty()) {
        cout << preOrder.front() << " ";
        preOrder.pop();
    }

    cout << endl << "Post order DFS of graph g" << endl;
    while(!postOrder.empty()) {
        cout << postOrder.front() << " ";
        postOrder.pop();
    }

    cout << endl << "Reverse post order DFS of graph g" << endl;

    while(!revPostOrder.empty()){
        cout << revPostOrder.top() << " ";
        revPostOrder.pop();
    }

    cout << endl << "A topological sort of graph topSort" << endl;
    auto topOrder = topSort.topologicalSort();
    for(int i = 0; i < topSort.size(); i++) {
        cout << topOrder.at(i) << " ";
    }

    cout << endl;

    return 0;
}


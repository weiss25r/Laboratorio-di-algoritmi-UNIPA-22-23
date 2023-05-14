//
// Created by weiss on 11/05/23.
//

#include "Digraph.h"
#include <iostream>
#include <fstream>
#include <deque>

Digraph::Digraph(int v) {
    adj = vector<Node*>(v, nullptr);
    numV = v;
    numE = 0;
}

Digraph::Digraph(std::ifstream inputFile) {
    //si assume che il file sia correttamente formattato
    int v, w;
    int e;

    inputFile >> numV;
    adj = vector<Node *>(numV, nullptr);

    numE = 0;

    inputFile >> e;

    for(int i = 0; i < e; i++) {
        inputFile >> v;
        inputFile >> w;
        insertEdge(v, w);
    }
}

void Digraph::insertEdge(int v, int u) {
    //insert edge (v, u);
    Node* list = adj.at(v);
    Node *prev = nullptr;

    if(list == nullptr) {
        adj.at(v) = new Node(u, nullptr);
    }

    else
    {
        while(list != nullptr)
        {
            prev = list;
            list = list->next;
        }

        list = new Node(u, nullptr);
        prev->next = list;
    }
    numE++;
}

void Digraph::freeList(Node *list) {
    Node *tmp;

    while(list != nullptr) {
        tmp = list;
        list = list->next;
        delete tmp;
    }
}

Digraph::~Digraph() {
    for(int i = 0; i < numV; i++) {
        freeList(adj.at(i));
    }
}

Digraph Digraph::reverse() {
    Digraph reverse(this->numV);

    for(int i = 0; i < this->numV; i++) {
        Node *list = adj.at(i);
        while(list != nullptr) {
            reverse.insertEdge(list->info, i);
            list = list->next;
        }
    }
    return reverse;
}

int Digraph::size() const{
    return numV;
}

const vector<Node *>& Digraph::getAdjList() const {
    return this->adj;
}

//alternative algorithm for topological sort
vector<int> Digraph::topologicalSort() {
    vector<int> inDregrees(numV);
    vector<int> topologicalSort;
    std::deque<int> zeros;
    //inizializzazione: calcola gli inDregrees di ogni nodo

    for(int i = 0; i < numV; i++) {
        Node *list = adj.at(i);
        while(list != nullptr) {
            inDregrees[list->info]++;
            list = list->next;
        }
    }

    //trova il primo nodo con in-degree 0


    for(int k = 0; k < numV; k++) {
        if(inDregrees[k] == 0) {
            zeros.push_back(k);
        }
    }

    /*
    if(k == numV) {
        std::cout << "Il grafo non ammette un ordinamento topologico" << std::endl;
    }
    */

    while(!zeros.empty())
    {
        int v = zeros.front();
        zeros.pop_front();
        topologicalSort.push_back(v);

        //aggiorna la tabella
        Node *list = adj.at(v);

        while(list != nullptr){
            inDregrees[list->info]--;
            if(inDregrees[list->info] == 0){
                zeros.push_back(list->info);
            }
            list = list->next;
        }
    }

    return topologicalSort;

}

void Digraph::printGraph()
{
    std::cout << "|V|: " << numV << std::endl << "|E|: " << numE << std::endl;
    for(int i = 0; i < numV; i++) {
        Node *tmp = adj[i];

        while(tmp != nullptr) {
            std::cout << i << "->" << tmp->info << std::endl;
            tmp = tmp->next;
        }
    }
}


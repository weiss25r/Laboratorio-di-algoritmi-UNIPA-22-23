//
// Created by Raffaele on 11/05/23.
//

#include "Digraph.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <list>

Digraph::Digraph(int v) {
    adj = vector<list<int>>(v);
    numV = v;
    numE = 0;
}

Digraph::Digraph(std::ifstream inputFile) {
    //si assume che il file sia correttamente formattato
    int v, w;
    int e;

    if(inputFile.is_open()) {
        inputFile >> numV;
        numE = 0;

        adj = vector<list<int>>(numV);

        inputFile >> e;

        for (int i = 0; i < e; i++) {
            inputFile >> v;
            inputFile >> w;
            insertEdge(v, w);
        }
    }
    else {
        std::cout << "Il file non è stato aperto correttamente" << std::endl;
        numV = 0;
        numE = 0;
    }
}

int Digraph::getNumV() const {
    return numV;
}

int Digraph::getNumE() const {
    return numE;
}

const vector<list<int>> &Digraph::getAdj() const {
    return adj;
}

void Digraph::insertEdge(int v, int w) {
    if(v >= 0 && w >= 0 && v < numV && w < numV) {
        adj[v].push_back(w);
        numE++;
    } else {
        std::cout << "Uno dei vertici specificati non esiste nel grafo" << std::endl;
    }
}

bool Digraph::pointsTo(int v, int w) {
    if(v >= 0 && w >= 0 && v < numV && w < numV) {
        return std::find(adj[v].begin(), adj[v].end(), w) != adj[v].end();
    }
    else return false;
}

const list<int> & Digraph::neighbours(int v) {
    if(v < 0 || v >= numV) {
        throw std::out_of_range("Il vertice specificato non esiste nel grafo");
    } else return adj[v];
}

void Digraph::printGraph()
{
    std::cout << "|V|: " << numV << std::endl << "|E|: " << numE << std::endl;
    for(int i = 0; i < numV; i++) {
        list<int> l = adj[i];

        for(int w : l) {
            std::cout << i << "->" << w << std::endl;
        }
    }
}

Digraph Digraph::reverse() {
    //(v, w) -> (w, v)
    Digraph reverse(this->numV);

    for(int i = 0; i < this->numV; i++) {
        list<int> l = adj[i];

        for(int w : l) {
            insertEdge(w, i);
        }

    }
    return reverse;
}


//alternative algorithm for topological sort
vector<int> Digraph::topologicalSort() {
    //si assume che il grafo sia un DAG
    vector<int> inDregrees(numV);
    vector<int> topologicalSort(numV);
    std::queue<int> zeros;

    int j = 0;

    //inizializzazione: calcola gli in-degrees di ogni nodo
    for(int i = 0; i < numV; i++) {
        list<int> l = adj[i];

        for(int w : l) {
            inDregrees[w]++;
        }
    }

    //trova il primo nodo con in-degree 0
    for(int k = 0; k < numV; k++) {
        if(inDregrees[k] == 0) {
            zeros.push(k);
        }
    }


    while(!zeros.empty())
    {
        int v = zeros.front();
        zeros.pop();
        topologicalSort[j++] = v;

        //aggiorna la tabella
        list<int> l = adj[v];

        for(int w : l){
            inDregrees[w]--;
            if(inDregrees[w] == 0){
                zeros.push(w);
            }
        }
    }

    return topologicalSort;

}











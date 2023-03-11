//
// Created by Raffaele on 11/03/2023.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include "binaryTree.h"

int main()
{
    BinaryTree *eren = createTree(1);
    insert(eren, 2, "ll");
    insert(eren, 3, "ll");
    insert(eren, 4, "rr");
    insert(eren, 5, "rl");
    insert(eren, 6, "rr");
    insert(eren, 7, "rr");
    insert(eren, 8, "rl");


    inOrder(eren);
    cout << endl;
    preOrder(eren);

    int p[] = {1, 2, 3, 4, 5};
    int i[] = {2, 3, 1, 5, 4};

    //BinaryTree *tree = createFrom(p, i, 0, 4, 0, 4);

    //inOrder(tree);
}
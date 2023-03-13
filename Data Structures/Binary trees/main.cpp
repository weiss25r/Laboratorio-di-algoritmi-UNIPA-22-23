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
    insertLeftTo(eren, 2);
    insertRightTo(eren->left, 3);
    insertRightTo(eren, 4);
    insertLeftTo(eren->right, 5);
    insertRightTo(eren->left->right, 6);
    insertLeftTo(eren->left, 11);
    insertRightTo(eren->right->left, 13);

    /*
    cout << "Visita in ordine simmetrico: ";
    inOrder(eren);
    cout << endl;

    cout << "Visita in pre ordine: ";
    preOrder(eren);
     */

    int p[] = {4, 6,  7, 1, 2, 3};
    int i[] = {7, 6, 1, 4, 2, 3};
    BinaryTree *tree = createFrom(p, i, 5, 0, 5);


    cout << "Visita in ordine simmetrico: ";
    inOrder(tree);
    cout << endl;

    cout << "Visita in pre ordine: ";
    preOrder(tree);

    int sequence[] = {9, 3, 7, 1, 8, 12, 10, 20, 15, 18, 5};

    /*
    BinaryTree *archimede = createArchimede(sequence, 0, 10);
    inOrder(archimede);
    */
}
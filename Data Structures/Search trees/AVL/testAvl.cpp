//
// Created by Raffaele on 24/04/2023.
//

#include <iostream>
#include "AvlTree.h"

int main()
{
    AvlTree avlTree(19);
    avlTree.insert(13);
    avlTree.insert(16);
    avlTree.insert(15);
    avlTree.insert(14);
    avlTree.remove(15);

    std::cout << avlTree;
}

#include <iostream>
#include <cstdlib>
#include "BstTree.h"
#include "AvlTree.h"
#include "FST//FstTree.h"

using namespace std;

void testBst()
{
    //random binary search tree
    const int kDim = 10;

    vector<int> keys(kDim);

    srand(time(nullptr));

    for(int i = 0; i < kDim; i++) {
        keys[i] = rand() % kDim + 1;
    }

    BstTree bst(keys);

    BstTree bst2(bst);
    cout << endl << bst2;
    bst2.remove(keys[kDim-1]);
    bst.insert(keys[kDim-1]+ 200);
    cout << bst2;
    cout << bst;

    BstTree bst3 = bst;
    bst3 = bst2;

    cout << bst3;
}

void testAvl()
{
    AvlTree avlTree(19);
    avlTree.insert(13);
    avlTree.insert(16);
    avlTree.insert(15);
    avlTree.insert(14);

    avlTree.remove(15);
    avlTree.remove(19);
    avlTree.remove(14);
    avlTree.remove(16);
    avlTree.remove(13);
    std::cout << avlTree;
}

int main() {
    FstTree fstTree;
    fstTree.insert(10);
    fstTree.insert(9);
    fstTree.insert(11);
    return 0;
}

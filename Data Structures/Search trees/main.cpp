#include <iostream>
#include <cstdlib>
#include "BstTree.h"

using namespace std;

int main() {
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

    return 0;
}

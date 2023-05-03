#include "BstTree.h"
#include "AvlTree.h"
#include "FST/FstTree.h"
#include "Splay Trees/SplayTree.h"

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

    BstTree<int> bst(keys);

    BstTree<int> bst2(bst);
    cout << endl << bst2;
    bst2.remove(keys[kDim-1]);
    bst.insert(keys[kDim-1]+ 200);
    cout << bst2;
    cout << bst;

    BstTree<int> bst3 = bst;
    bst3 = bst2;

    cout << bst3;
}

void testAvl()
{
    AvlTree<int> avlTree(19);
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

void testFst() {
    FstTree<int> fstTree;
    fstTree.insert(10);
    fstTree.insert(9);
    fstTree.insert(11);
    fstTree.inOrder();
}

void testSplay()
{
    SplayTree<int> splayTree;
    splayTree.climbInsert(10);
    splayTree.climbInsert(11);
    splayTree.climbInsert(9);
    splayTree.climbInsert(12);
    //splayTree.inOrder();
    splayTree.climbInsert(13);
    //splayTree.inOrder();

    splayTree.climbInsert(14);
    //splayTree.inOrder();
    splayTree.climbInsert(16);
    //splayTree.inOrder();
    splayTree.climbInsert(0);
    //splayTree.inOrder();
    splayTree.climbInsert(1);
    splayTree.climbInsert(2);
    splayTree.climbInsert(20);
    splayTree.climbInsert(3);
    splayTree.climbInsert(4);
    splayTree.inOrder();
}

int main()
{
    testSplay();
    return 0;
}

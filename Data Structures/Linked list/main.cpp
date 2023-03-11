#include <iostream>
#include <cstdlib>
#include "list.h"

int main()
{
    List *list = createList(1);
    insert(list, 2);
    insert(list, 3);
    insert(list, 4);
    insert(list, 5);
    insert(list, 6);
    insert(list, 7);
    insert(list, 8);

    printList(list);

    orderOddEven(list);
    printList(list);

    //reverse(list);
    freeList(list);
}
#include <iostream>
#include <cstdlib>
#include "list.h"

int main(void)
{
    List *list = createList(1);
    insert(list, 2);
    insert(list, 3);
    printList(list);

    reverse(list);
    printList(list);
    freeList(list);
}
struct List {
    int info;
    List *next;
};

List *createList(int info);
void insert(List *head, int info);
void printList(List *head);
void freeList(List *head);
void reverse(List *head);
void orderOddEven(List *head);
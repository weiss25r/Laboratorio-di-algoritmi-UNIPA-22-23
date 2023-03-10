#include <iostream>
#include <cstdlib>
#include "list.h"

using namespace std;

List *createList(int info) {
    List *head = new List;
    head->info = info;
    head->next = nullptr;
    return head;
}

void insert(List *head, int info) 
{
    List *node = new List;
    node->next = nullptr;
    node->info = info;

    List *ptr = head;

    while (ptr->next != nullptr) {
        ptr = ptr->next;
    }

    ptr->next = node;
}

void printList(List *head){
    List *ptr = head;

    cout << "List: " << endl;

    while(ptr != nullptr) {
        cout << ptr->info << "->";
        ptr = ptr->next;
    }

    cout << endl;
}

void reverse(List *head) {
    if(head->next==nullptr) {
        return;
    }

    //cerca il punto di mezzo della lista
    List *ptr, *ptrHalf;
    ptr = head;
    ptrHalf = ptr;
    
    while (ptr->next != nullptr) {
        ptr = ptr->next->next;
        ptrHalf = ptrHalf->next;
    }

    List *sx = ptrHalf->next;
    ptr = head->next;

    //scambia tutti gli elementi tranne testa e coda
    while (sx->next != nullptr)
    {
        int tmp = ptr->info;
        ptr->info = sx->info;
        sx->info = tmp;

        ptr = ptr->next;
        sx = sx->next;
    }
    
    //scambia testa e coda
    int tmp = head->info;
    head->info = sx->info;
    sx->info = tmp;
}

void freeList(List *head) {
    List *prev;

    while (head !=nullptr) {
        prev = head;
        head = head->next;
        delete prev;
    }
    
}
//
// Created by Raffaele on 11/03/2023.
//

#include <iostream>
#include <cstdlib>
#include "stack.h"

using namespace std;

StackNode *stackPtr;

void stackInit() {
    stackPtr = nullptr;
}

bool stackIsEmpty() {
    return stackPtr == nullptr;
}

void push(int info) {
    //TODO: check...
    auto *node = new StackNode;
    node->info = info;
    node->next = stackPtr;
    stackPtr = node;
}

char pop() {
    //TODO: check...
    int info = stackPtr->info;
    StackNode *newHead = stackPtr->next;
    delete stackPtr;
    stackPtr = newHead;

    return info;
}

char peek() {
    //TODO: check...
    return stackPtr->info;
}

void printStack() {
    StackNode *ptr = stackPtr;

    while(ptr != nullptr) {
        cout << ptr->info << "->";
        ptr = ptr->next;
    }

    cout << endl;
}

void freeStack() {
    while(stackPtr != nullptr) {
        pop();
    }
}
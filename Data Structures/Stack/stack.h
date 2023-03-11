//
// Created by Raffaele on 11/03/2023.
//

#ifndef LABORATORIO_DI_ALGORITMI_UNIPA_22_23_STACK_H
#define LABORATORIO_DI_ALGORITMI_UNIPA_22_23_STACK_H

#endif //LABORATORIO_DI_ALGORITMI_UNIPA_22_23_STACK_H

struct StackNode {
    char info;
    StackNode *next;
};

void stackInit();
void push(int info);
char pop();
char peek();
bool stackIsEmpty();
void printStack();
void freeStack();
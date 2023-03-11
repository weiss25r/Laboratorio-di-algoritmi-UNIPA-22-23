//
// Created by Raffaele on 11/03/2023.
//

#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

int main()
{
    string input;
    cout << "Inserisci una sequenza di parentesi: ";
    cin >> input;

    stackInit();
    int i;

    for (i = 0; i < input.length(); i++) {
        if(input[i] == ('(') || input[i] == ('[') || input[i] == '{') {
            push(input[i]);
        }
        else {
            if(!stackIsEmpty())
                pop();
            else break;
        }
    }

    if(stackIsEmpty() && i == input.length()) {
        cout << "Sequenza accettata" << endl;
    } else {
        cout << "Sequenza non valida" << endl;
        freeStack();
    }
}
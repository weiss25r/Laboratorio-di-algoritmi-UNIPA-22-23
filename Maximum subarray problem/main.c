#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maxSum.h"


int main(void) 
{
    int n;
    double *array, maxSum;
    time_t start, end;

    srand(time(NULL));

    printf("Inserisci la dimensione dell'array: ");
    scanf("%d", &n);

    array = malloc(sizeof(double)*n);

    //riempie casualmente l'array
    for(int i = 0; i < n; i++) {
        double x = rand();
        array[i] = x* ( (int)x % n ? 1 : -1);
    }

    start = clock();
    maxSum = maxSumNaive(array, n);
    end = clock();

    printf("Somma massima maxSumNaive: %.3f\n, tempo passato: %f secondi\n", maxSum, (double)(end-start)/CLOCKS_PER_SEC);
    
    start = clock();
    maxSum = maxSumQuadratic(array, n);
    end = clock();

    printf("Somma massima maxSumQuadratic: %f, tempo passato: %f secondi\n", maxSum, (double)(end-start)/CLOCKS_PER_SEC);
    
    start = clock();
    maxSum = maxSumCumulative(array, n);
    end = clock();    
    
    printf("Somma massima maxSumCumulative: %f, tempo passato: %f secondi\n", maxSum, (double)(end-start)/CLOCKS_PER_SEC);

    start = clock();
    maxSum = maxSumRecursive(array, 0, n-1);
    end = clock();    

    printf("Somma massima maxSumRecursive: %f, tempo passato: %f secondi\n", maxSum, (double)(end-start)/CLOCKS_PER_SEC);

    start = clock();
    maxSum = maxSumLinear(array, n);
    end = clock();   

    printf("Somma massima maxSumLinear: %f, tempo passato: %f secondi\n", maxSum, (double)(end-start)/CLOCKS_PER_SEC);

    free(array);
}
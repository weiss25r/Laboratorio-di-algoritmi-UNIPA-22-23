#include <stdio.h>
#include <stdlib.h>
#include "maxSum.h"

double max(double a, double b) {
    return a > b ? a : b;
}


double maxSumNaive(double *array, int n) {
    double maxSoFar = 0;

    for (int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            double sum = 0;

            for(int k = i; k <= j; k++) {
                sum += array[k];
            }

            if(sum > maxSoFar) {
                maxSoFar = sum;
            }
        }
    }

    return maxSoFar;
}

double maxSumQuadratic(double *array, int n) {
    double maxSoFar = 0;

    for (int i = 0; i < n; i++) {
        double sum = 0;

        for(int j = i; j < n; j++) {
            sum += array[j];
            
            if(maxSoFar < sum) {
                maxSoFar = sum;
            }
        }
    }

    return maxSoFar;
}

double maxSumCumulative(double *array, int n) {
    double *cumArray = calloc(n, sizeof(double));

    for(int i = 1; i <= n; i++) {
        cumArray[i] = cumArray[i-1]+array[i-1];
    }

    double maxSoFar = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            double sum = cumArray[j]-cumArray[i-1];
            
            if(maxSoFar < sum) {
                maxSoFar = sum;
            }
        }
    }

    return maxSoFar;
}

double maxSumRecursive(double *array, int left, int right) {
    //base della ricorsione
    if(left > right) {
        return 0;
    }
   
    else if(left == right) {
        return array[left] > 0 ? array[left] : 0;
    }

     else {
        //si computa il punto centrale dell'array 
        int middle = (left + right)/2;

        double sum = 0;

        double maxLeft = 0, maxRight = 0;
        
        //si computa la parte sinistra di Mc (da middle a left)
        for (int i = middle; i >= left; i--) {
            sum += array[i];

            if(maxLeft < sum) {
                maxLeft = sum;
            }
        }

        sum = 0;

        //si computa la parte destra di Mc (da middle a left)
        for (int i = middle+1; i <= right; i++) {
            sum += array[i];

            if(maxRight < sum) {
                maxRight = sum;
            }
        }

        //si computa il massimo nel sottoarray a cavallo tra A e B        
        double maxC = maxLeft+maxRight;

        //passo ricorsivo
        double maxA = maxSumRecursive(array, left, middle);
        double maxB = maxSumRecursive(array, middle+1, right);

        //confronto finale

        if(maxA > maxB && maxA > maxC)
            return maxA;
        else if(maxB > maxA && maxB > maxC)
            return maxB;
        else return maxC;
    }
}

double maxSumLinear(double *array, int n) {
    double maxEndingHere = 0;
    double maxSoFar = 0;

    for(int i = 0; i < n; i++) {
        maxEndingHere = max(0, maxEndingHere + array[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }

    return maxSoFar;
}
#include "combine.hpp"
#include <iostream>

double combine(const double arr[], int countElems, FuncT mult, FuncT plus) {
    double multResults[countElems/2==0 ? countElems/2 : countElems/2+1];
    double finalRes=0;

    if (countElems == 1) {
        return arr[0];
    }

    for (int i = 0; i < countElems; i++) {
        if (i%2!=0) {
            multResults[(i-1)/2] = mult(arr[i-1], arr[i]);
        }
    }

    if (countElems%2==1) {
        multResults[countElems/2] = arr[countElems-1];
    }

    if (countElems%2==0) {
        for (int i=0; i<countElems/2; i++) {
            finalRes = plus(multResults[i], finalRes);
        }
    } else {
        for (int i=0; i<countElems/2; i++) {
            finalRes = plus(multResults[i], finalRes);
        }
        finalRes += multResults[countElems/2];
    }


    return finalRes;
}

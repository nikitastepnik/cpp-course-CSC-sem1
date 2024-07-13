#include "compute_fib.hpp"

#include <iostream>
#include <fstream>

int64_t compute_fib() {
    int fibPrevVal = 0;
    int fibCurVal = 1;
    int fibNextVal = 0;
    int fibNumber;

    std::ifstream in("input.txt");
    in >> fibNumber;

    if (fibNumber == 0) {
        return 0;
    }
    if (fibNumber == 1) {
        return 1;
    }

    for (int i=2; i <= fibNumber; i++) {
        fibNextVal = fibCurVal + fibPrevVal;
        fibPrevVal = fibCurVal;
        fibCurVal = fibNextVal;
    }

    return fibNextVal;
}


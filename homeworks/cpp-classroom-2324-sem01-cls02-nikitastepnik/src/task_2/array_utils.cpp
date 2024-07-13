#include "array_utils.hpp"

#include <map>
#include <iostream>
#include <vector>


int sum(const_int_pointer_t a, size_t s) {
    int sum = 0;
    for (size_t i = 0; i < s; i++) {
        sum += a[i];
    }
    return sum;
}

int countNumbers(const_int_pointer_t a, size_t s) {
    std::map<int, int> countNumbers;

    for (size_t i = 0; i < s; i++) {
        if (countNumbers.count(a[i]) > 0) {
            countNumbers[a[i]] += 1;
        } else {
            countNumbers[a[i]] = 1;
        }
    }

    int countUniqNumbers = 0;

    for (auto it = countNumbers.begin(); it != countNumbers.end(); ++it) {
        countUniqNumbers += 1;
    }

    return countUniqNumbers;
}

//void popZeros(const_int_pointer_t *a, size_t s) {
//    const int *curElem;
//
//    for (int i = 0; i < s; i++) {
//        if (a[i] == nullptr) {
//            continue;
//        }
//        if (*a[i] == 0) {
//            for (int j = (int) s - 1; j >= i; j--) {
//                if (a[j] != nullptr) {
//                    if (*a[j] == 0) {
//                        continue;
//                    }
//                }
//                curElem = a[i];
//                a[i] = a[j];
//                a[j] = curElem;
//                break;
//            }
//        }
//
//    }

void popZeros(const_int_pointer_t* a, size_t size) {
    std::vector<const_int_pointer_t> nonZeroValues;
    std::vector<const_int_pointer_t> zeroValues;

    for (size_t i = 0; i < size; ++i) {
        if (a[i] == nullptr) {
            nonZeroValues.push_back(a[i]);
            continue;
        }
        if (*a[i] == 0) {
            zeroValues.push_back(a[i]);
        } else {
            nonZeroValues.push_back(a[i]);
        }
    }

    size_t nonZeroCount = nonZeroValues.size();

    for (size_t i = 0; i < nonZeroCount; ++i) {
        a[i] = nonZeroValues[i];
    }

    for (size_t i = nonZeroCount; i < size; ++i) {
        a[i] = zeroValues[i - nonZeroCount];
    }
}



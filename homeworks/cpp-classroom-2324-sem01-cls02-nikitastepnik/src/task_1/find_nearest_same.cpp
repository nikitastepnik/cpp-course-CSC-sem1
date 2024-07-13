#include "find_nearest_same.hpp"

ptrdiff_t findNearestSame(const char* s, const char* c) {
    std::ptrdiff_t r = 0, r_temp = 0;
    for (char*  j = (char*)(c + 1); *j != '\0'; j++) {
        r_temp++;
        if (*j == *c) {
            r = r_temp;
            break;
        }
    }

    std::ptrdiff_t l = 0, l_temp = 0;
    for (char* j = (char*)(c - 1); j != s - 1; j--) {
        l_temp--;
        if (*j == *c) {
            l = l_temp;
            break;
        }
    }

    if (r != 0 && l != 0) {
        if (l * -1 < r) {
            return l;
        }
        return r;
    }
    if (r != 0) {
        return r;
    }
    if (l != 0) {
        return l;
    }

    return 0;
}

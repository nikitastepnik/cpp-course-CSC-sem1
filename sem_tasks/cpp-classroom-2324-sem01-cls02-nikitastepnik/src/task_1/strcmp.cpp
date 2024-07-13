#include "strcmp.hpp"

int myStrCmp(const char *s1, const char *s2) {
    while (*s1 == *s2 && *s1) {
        s1++;
        s2++;
    }
    if (*s1 && *s2) {
        return *s1 - *s2;
    }
    if (*s1 && !*s2) {
        return 1;
    }
    if (!*s1 && *s2) {
        return -1;
    }
    return 0;
}

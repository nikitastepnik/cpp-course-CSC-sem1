#include "composition.hpp"
#include <iostream>

double Compose(size_t n, ...) {
    std::va_list args;
    va_start(args, n);

    for (size_t i = 0; i < n; i++)
    {
    }

    double arg = va_arg(args, double);

    va_end(args);

    va_start(args, n);

    for (size_t i = n; i > 0; i--)
    {
        FuncT func = va_arg(args, FuncT);
        arg=func(arg);
    }

    va_end(args);

    return arg;
}

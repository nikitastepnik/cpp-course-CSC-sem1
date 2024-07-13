#pragma once

#include <cstring>
#include <cstdarg>

using FuncT = double(*)(double);

// Композиция всех переданных функций
double Compose(size_t n, ...);

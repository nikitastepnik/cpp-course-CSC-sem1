#pragma once

using FuncT = double(*)(double, double);
double combine(const double arr[], int countElems, FuncT mult, FuncT plus);
#pragma once

#include <math.h>   //abs, pow
#include <stdio.h>
#include <stdlib.h>

typedef double (*func)(double);
typedef double (*func2)(double,double);

// double df_forward(func f, double x, double h)
// {
//     return (f(x + h) - f(x)) / h;
// }

// double df_forward(double (*f)(double), double x, double h)
// {
//     return (f(x + h) - f(x)) / h;
// }

typedef struct xy_t
{
    double x, y;
} xy, *pxy;

typedef struct xyn_t
{
    xy* values;
    xy lastValue;
    int count;
} xyn, *pxyn;


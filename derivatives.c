#include "derivatives.h"

double df_forward(func f, double x, double h)
{
    return (f(x + h) - f(x)) / h;
}

double df_backward(func f, double x, double h)
{
    return (f(x) - f(x - h)) / h;
}

double df_central(func f, double x, double h)
{
    return (f(x + h) - f(x - h)) / 2.0 / h;
}

double df_central2(func f, double x, double h)
{
    return (f(x + h / 2.0) - f(x - h / 2.0)) / h;
}

double df2_central(func f, double x, double h)
{
    return (f(x + h) + f(x - h) - 2.0 * f(x)) / h / h;
}
#pragma once

#include <stdlib.h> //malloc
#include <stdio.h>  //printf

#include "common.h"


// // y'=f(x,y)
// double rk1(double (*f)(double, double), double x0, double y0, double h)
// {
//     return y0 + h * f(x0 + h, y0);
// }



xy *rk1(double (*f)(double, double), double x0, double y0, double xn, int intervals)
{
    double h = (xn - x0) / (double)intervals;

    xy *values = malloc((intervals + 1) * sizeof(xy));
    values[0] = (xy){.x = x0, .y = y0};

    for (size_t i = 1; i <= intervals; i++)
    {
        double x = values[i - 1].x, y = values[i - 1].y;

        double k1 = h * f(x, y);

        x = x0 + i * h;
        y += k1;
        values[i] = (xy){.x = x, .y = y};
    }
    return values;
}

xy *rk4(double (*f)(double, double), double x0, double y0, double xn, int intervals)
{
    double h = (xn - x0) / (double)intervals;
#ifdef DEBUG
    printf("x0 = %lf, y0 = %lf, n= %ld, h = %lf\n", x0, y0, intervals, h);
#endif

    xy *values = malloc((intervals + 1) * sizeof(xy));
    values[0] = (xy){.x = x0, .y = y0};

    for (size_t i = 1; i <= intervals; i++)
    {
        double x = values[i - 1].x, y = values[i - 1].y;

        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 2.0, y + k1 / 2.0);
        double k3 = h * f(x + h / 2.0, y + k2 / 2.0);
        double k4 = h * f(x + h, y + k3);

        x = x0 + i * h;
        y += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
        values[i] = (xy){.x = x, .y = y};

#ifdef DEBUG
        printf("Step: %ld\n  k1 = %lf\n", i, k1);
        printf("  k2 = %lf\n", k2);
        printf("  k3 = %lf\n", k3);
        printf("  k4 = %lf\n", k4);
        printf("  x = %lf, y = %lf\n\n", x, y);
#endif
    }
    return values;
}

void disposeXyn(xyn v)
{
    free(v.values);
    v.count = 0;
}

// Runge-Kutta-Fehlberg (RK45)
xyn rk45(double (*f)(double, double), double x0, double y0, double xn, double h0, double epsilon)
{
    double h = h0;
#ifdef DEBUG
    printf("Step: #%ld, x = %lf, y = %lf, h = %lf\n", 0, x0, y0, h0);
#endif

    size_t steps = 1ul;
    xy *values = malloc(sizeof(xy));
    values[steps-1] = (xy){.x = x0, .y = y0};

    double x = x0, y = y0;

#ifdef DEBUG
    size_t calculations = 0ul;
#endif

    while (x < xn)
    {
        if (h >= xn - x)
            h = xn - x;

        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 4.0, y + k1 / 4.0);
        double k3 = h * f(x + h * 3.0 / 8.0, y + k1 * 3.0 / 32.0 + k2 * 9.0 / 32.0);
        double k4 = h * f(x + h * 12.0 / 13.0, y + k1 * 1932.0 / 2197.0 - k2 * 7200.0 / 2197.0 + k3 * 7296.0 / 2197.0);
        double k5 = h * f(x + h, y + k1 * 439.0 / 216.0 - k2 * 8.0 + k3 * 3680.0 / 513.0 - k4 * 845.0 / 4104.0);
        double k6 = h * f(x + h / 2.0, y - k1 * 8.0 / 27.0 + k2 * 2.0 - k3 * 3544.0 / 2565.0 + k4 * 1859.0 / 4104.0 - k5 * 11.0 / 40.0);

        double y1 = y + k1 * 25.0 / 216.0 + k3 * 1408.0 / 2565.0 + k4 * 2197.0 / 4104.0 - k5 / 5.0;
        double y2 = y + k1 * 16.0 / 135.0 + k3 * 6656.0 / 12825.0 + k4 * 28561.0 / 56430.0 - k5 * 9.0 / 50.0 + k6 * 2.0 / 55.0;
        double r = fabs(y1 - y2) / h;
        double delta = 0.84 * pow(epsilon / r, 0.25);

#ifdef DEBUG
        printf("   Calc Step: #%ld\n   k1 = %lf\n", ++calculations, k1);
        printf("   k2 = %lf\n", k2);
        printf("   k3 = %lf\n", k3);
        printf("   k4 = %lf\n", k4);
        printf("   k5 = %lf\n", k5);
        printf("   k6 = %lf\n", k6);
        printf("   x = %lf, y = %lf\n\n", x, y1);
#endif

        if (r <= epsilon)
        {
            x += h;
            //keep the solution
            y = y1;
            values = realloc(values, sizeof(xy) * ++steps);
            values[steps - 1] = (xy){.x = x, .y = y};

#ifdef DEBUG
        printf("Step: #%ld, x = %lf, y = %11.9lf, h = %lf\n", steps-1, x, y, h);
#endif
        }

        h *= delta;
    }

    return (xyn){.values = values, .count = steps, .lastValue = values[steps-1]};
}
#pragma once

#include "common.h"

typedef struct rootFinder_t
{
    double x;     // current root estimation
    double fx;    // current f(x)
    double e;     // current relative error
    size_t steps; // current number of calculation steps
} rootFinder, *pRootFinder;


/*
Root solver using the bisection method.
xl: x left
xu: x upper
epsilon: acceptable relative error
Example:
double ftosolve(double x)
{
    return sqrt(2)-x;
}
void testSolver()
{
    rootFinder result = bisect(ftosolve, 1, 10, 1e-5, 1e8);
    printf("Found result: %lf in %ld steps.\n", result.x,result.steps);
}
*/
rootFinder bisect(func f, double xl, double xu, double epsilon, long maxIterations)
{
    size_t steps = 0;
    double fl = f(xl);

    double error, fr, xr = xl;

    do
    {
        steps++;
        double xrold = xr;
        xr = (xl + xu) / 2.0;
        fr = f(xr);
        //if (xr != 0.0)
        //    error = fabs((xr - xrold) / xr);
        error = fabs(fr);
        double test = fl * fr;
        if (test < 0.0)
        {
            xu = xr;
#ifdef DEBUG
            printf("Step #%ld (xr -> xu), xl = %lf, xu = %lf, xr = %lf\n", steps, xl, xu, xr);
#endif
        }
        else if (test > 0.0)
        {
            xl = xr;
            fl = fr;
#ifdef DEBUG
            printf("Step #%ld (xr -> xl), xl = %lf, xu = %lf, xr = %lf\n", steps, xl, xu, xr);
#endif
        }
        else
            error = 0.0;

    } while (error >= epsilon && steps < maxIterations);

    return (rootFinder){.x = xr, .fx = fr, .e = error, .steps = steps};
}

rootFinder regulaFalsi(func f, double xl, double xu, double epsilon, long maxIterations)
{
    size_t steps = 0;
    double fl = f(xl), fu = f(xu);
    double error, fr, xr = xl;

    do
    {
        steps++;
        double xrold = xr;
        xr = xu - fu * (xl - xu) / (fl - fu); //(xl + xu) / 2.0;
        fr = f(xr);
        //if (xr != 0.0)
        //    error = fabs((xr - xrold) / xr);
        error = fabs(fr);
        double test = fl * fr;
        if (test < 0.0)
        {
            xu = xr;
            fu = fr;
#ifdef DEBUG
            printf("Step #%ld (xr -> xu), xl = %lf, xu = %lf, xr = %lf\n", steps, xl, xu, xr);
#endif
        }
        else if (test > 0.0)
        {
            xl = xr;
            fl = fr;
#ifdef DEBUG
            printf("Step #%ld (xr -> xl), xl = %lf, xu = %lf, xr = %lf\n", steps, xl, xu, xr);
#endif
        }
        else
            error = 0.0;

    } while (error >= epsilon && steps < maxIterations);

    return (rootFinder){.x = xr, .fx = fr, .e = error, .steps = steps};
}

rootFinder regulaFalsiModified(func f, double xl, double xu, double epsilon, long maxIterations)
{
    size_t steps = 0;
    double fl = f(xl), fu = f(xu);
    double error, fr, xr = xl;

    size_t iu = 0ul, il = 0ul;

    do
    {
        steps++;
        double xrold = xr;
        xr = xu - fu * (xl - xu) / (fl - fu); 
        fr = f(xr);
        //if (xr != 0.0)
        //    error = fabs((xr - xrold) / xr);
        error = fabs(fr);
        double test = fl * fr;
        if (test < 0.0)
        {
            xu = xr;
            fu = fr;

            iu=0ul; il++;
            if(il>=2) fl/=2;
#ifdef DEBUG
            printf("Step #%ld (xr -> xu), xl = %lf, xu = %lf, xr = %lf, il = %ld\n", steps, xl, xu, xr, il);
#endif
        }
        else if (test > 0.0)
        {
            xl = xr;
            fl = fr;
            iu++; il=0ul;
            if(iu>=2) fu/=2;

#ifdef DEBUG
            printf("Step #%ld (xr -> xl), xl = %lf, xu = %lf, xr = %lf, iu = %ld\n", steps, xl, xu, xr, iu);
#endif
        }
        else
            error = 0.0;

    } while (error >= epsilon && steps < maxIterations);

    return (rootFinder){.x = xr, .fx = fr, .e = error, .steps = steps};
}
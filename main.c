#include "mylib.h"

#include <unistd.h>

#include "compiler.h"

#define DEBUG
#include "rk.h"

#include "solver.h"
#include "solveScenarios.h"

double kf(double x)
{
    return 10 * x * x;
}

double ftest(double x, double y)
{
    //return y - x * x + 1.0;
    return 1+y*y;
}

void testSolver()
{
    solveScenario scenario = getSampleScenario(SOLVEPOW10);
    solve(&scenario);
}

int main(int argc, char **argv)
{
    testSolver(); return 0;

    // printf("The value is %lf\n",df2_central(kf,3,0.001));

    // simpleTests();

    // printf("%ld\n",__STDC_VERSION__);
    // printf("%ld\n",__STDC__);
    // printf("%ld\n",__STDC_HOSTED__);

    // puts(GetCVersion());
    // printf("%ld\n",__BOOL__); //always defined??

    int intervals = 4;

    //puts("Simple RK4:");
    //pxy values = rk4(ftest, 0.0, 0.5, 2.0, intervals); // allocate
    // for (size_t i = 0; i <= intervals; i++)
    //     printf("Step %ld: x = %4.2lf, y = %11.9lf\n", i, values[i].x, values[i].y);
    //free(values);

    puts("RK45:");
    double h0 = 0.1;
    //xyn v2 = rk45(/*f*/ ftest, /*x0*/ 0.0, /*y0*/ 0.5, /*xn*/  2.0, /*h0*/ h0, /*epsilon*/ 1e-8);
    xyn v2 = rk45(/*f*/ ftest, /*x0*/ 0.0, /*y0*/ 0.0, /*xn*/  1.4, /*h0*/ h0, /*epsilon*/ 1e-5);
    // for (size_t i = 0; i < v2.count; i++)
    // {
    //     xy v = v2.values[i];
    //     double h = i>0 ? v.x - v2.values[i-1].x : h0;
    //     printf("Step %ld: x = %lf, y = %11.9lf, h = %lf\n", i, v.x, v.y, h);
    // }
    xy result = v2.lastValue;
    printf("Result: step %ld, x = %lf, y = %11.9lf\n", v2.count, result.x, result.y);
    disposeXyn(v2);

    return 0;
}

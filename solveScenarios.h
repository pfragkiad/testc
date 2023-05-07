#pragma once

#include "solver.h"


enum SolveScenarios
{
    SOLVE1, //first example
    SOLVEPOW10
};

double fToSolve1(double x)
{
    return 668.06/x *(1-exp(-0.146843*x))-40.0;
}

double fToSolve10(double x)
{   
    return pow(x,10.0)-1;
}

typedef struct solveScenario_t
{
    func f;
    double from, to, epsilon;
    size_t maxIterations;
} solveScenario, *pSolveScenario;


solveScenario getSampleScenario(enum SolveScenarios scenario)
{
    size_t maxIterations = 1e8;

    switch (scenario)
    {
        case SOLVE1:
            return (solveScenario){.f = fToSolve1, .from =12.0, .to=16.0,.epsilon = 1e-5, .maxIterations = maxIterations};
        case SOLVEPOW10:
            return (solveScenario){.f = fToSolve10,.from=0.0,.to = 1.3,.epsilon = 1e-4,.maxIterations = maxIterations};
    }
}

void solve(solveScenario* scenario)
{
    puts("Bisection");
    rootFinder result = bisect(scenario->f,scenario->from,scenario->to,scenario->epsilon,scenario->maxIterations);
    printf("Found result: %lf in %ld steps.\n", result.x,result.steps);

    puts("\nRegula Falsi");
    //result = regulaFalsi(ftosolve,1,10,1e-5,1e8);
    result = regulaFalsi(scenario->f,scenario->from,scenario->to,scenario->epsilon,scenario->maxIterations);
    printf("Found result: %lf in %ld steps.\n", result.x,result.steps);

    puts("\nRegula Falsi modified");
    result = regulaFalsiModified(scenario->f,scenario->from,scenario->to,scenario->epsilon,scenario->maxIterations);
    printf("Found result: %lf in %ld steps.\n", result.x,result.steps);
}

#pragma once

#include "common.h"

double df_forward(func f, double x, double h);

double df_backward(func f, double x, double h);

double df_central(func f, double x, double h);

double df_central2(func f, double x, double h);

double df2_central(func f, double x, double h);
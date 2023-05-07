#pragma once

#include <stdbool.h>

enum CStandard
{
    Legacy,
    C89 = 1L,
    C90 = 1L,
    C94 = 199409L,
    C99 = 199901L,
    C11 = 201112L,
    C18 = 201710L
};

int isAtLeastC18();

int isAtLeastC11();

int isAtLeastC99();

int isAtLeastC94();

int isAtLeastStandardC();

const char* getCVersion();
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

int IsAtLeastC18();

int IsAtLeastC11();

int IsAtLeastC99();

int IsAtLeastC94();

int IsAtLeastStandardC();

const char* GetCVersion();
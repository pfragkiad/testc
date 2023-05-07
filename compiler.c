#include "compiler.h"


int IsAtLeast(long version)
{
#ifdef __STDC_VERSION__
    return __STDC_VERSION__ >= version;
#endif
    return 0;
}

int isAtLeastC18()
{
    return IsAtLeast(C18);
}

int isAtLeastC11()
{
    return IsAtLeast(C11);
}

int isAtLeastC99()
{
    return IsAtLeast(C99);
}

int isAtLeastC94()
{
    return IsAtLeast(C94);
}

int isAtLeastStandardC()
{
#ifdef __STDC__
    return __STDC__ == 1;
#endif
    return 0;
}

const char* getCVersion()
{
    //content based on https://sourceforge.net/p/predef/wiki/Standards/
    if(isAtLeastC18) return "ISO/IEC 9899:2018";
    if(isAtLeastC11) return "ISO/IEC 9899:2011";
    if(isAtLeastC99) return "ISO/IEC 9899:1999";
    if(isAtLeastC94) return "ISO/IEC 9899-1:1994";
    if(isAtLeastStandardC()) return "ISO/IEC 9899:1990";
    return "Non-standard C";
}
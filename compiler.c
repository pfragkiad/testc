#include "compiler.h"


int IsAtLeast(long version)
{
#ifdef __STDC_VERSION__
    return __STDC_VERSION__ >= version;
#endif
    return 0;
}

int IsAtLeastC18()
{
    return IsAtLeast(C18);
}

int IsAtLeastC11()
{
    return IsAtLeast(C11);
}

int IsAtLeastC99()
{
    return IsAtLeast(C99);
}

int IsAtLeastC94()
{
    return IsAtLeast(C94);
}

int IsAtLeastStandardC()
{
#ifdef __STDC__
    return __STDC__ == 1;
#endif
    return 0;
}

const char* GetCVersion()
{
    //content based on https://sourceforge.net/p/predef/wiki/Standards/
    if(IsAtLeastC18) return "ISO/IEC 9899:2018";
    if(IsAtLeastC11) return "ISO/IEC 9899:2011";
    if(IsAtLeastC99) return "ISO/IEC 9899:1999";
    if(IsAtLeastC94) return "ISO/IEC 9899-1:1994";
    if(IsAtLeastStandardC()) return "ISO/IEC 9899:1990";
    return "Non-standard C";
}
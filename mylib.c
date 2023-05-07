#include "mylib.h"

void f(const float *i) {
    printf("%f\n", *i);
}

void simpleTests()
{
    puts("KEFASDASD!\n");
    int v = 20;

    f(&(float){1.0f});
    f2(&(float){1.0f});
}

void f2(float const *i) {
    printf("%f\n", *i);
}

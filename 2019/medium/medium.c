#include <stdio.h>

#define SWAP(T, a, b) \
    do { \
        T tmp = a; \
        a = b; \
        b = tmp; \
    } while(0)

void swap(int* a, int* b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int main()
{
    int a = 42;
    int b = 666;
    SWAP(int, a, b);

    printf("a: %i, b: %i\n", a, b);
    return 0;
}
#include <stdio.h>


void foo(char *ptr)
{
    if(*ptr != '\0') {
        putchar(*ptr);
        foo(++ptr);
    }
}


int main()
{
    char bar[] = "mystring!";
    foo(bar);
    putchar('\n');
}

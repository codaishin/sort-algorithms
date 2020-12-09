#include <stdio.h>

void fibonnaci(int* array, size_t size, size_t start, size_t end)
{
    int before_two = 0;
    int before_one = 1;
    int tmp;
    for (size_t i = 2; i < start; ++i) {
        tmp = before_one;
        before_one = before_one + before_two;
        before_two = tmp;
    }
    array[0] = before_two + before_one;
    array[1] = before_one + array[0];
    for (size_t i = 2; i < size; ++i) {
        array[i] = array[i-1] + array[i-2];
    }
}


int main()
{
    int start = 10;
    int end = 20;
    size_t size = end - start + 1;
    int array[size];

    fibonnaci(array, size, start, end);
    for(size_t i = 0; i < size; ++i) {
        printf("%i ", array[i]);
    }
    printf("\n");
    return 0;
}

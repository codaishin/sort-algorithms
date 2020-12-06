#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "array_tools.h"
void arr_ascending(int* array, size_t size)
{
    for(size_t i = 0; i < size; ++i) {
        array[i] = i;
    }
}

error_t arr_random(int* array, size_t size, int lower, int upper)
{
    srand(time(NULL));
    if(lower >= upper) {
        return INVALID_BOUNDS;
    }
    for (size_t i = 0; i < size; ++i) {
        array[i] = rand() % (upper - lower - 1) + lower + 1;
    }
    return SUCCESS;
}

void arr_print(int* array, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        printf("%i ", array[i]);
    }
    printf("\n");
}

bool test_sorted(int* array, size_t size, size_t* index_ptr)
{
    bool okay = true;
    for (size_t i = 1; i < size && okay; ++i) {
        if (array[i-1] > array[i]) {
            okay = false;
            *index_ptr = i - 1;
        }
    }
    return okay;
}

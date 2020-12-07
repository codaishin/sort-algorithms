#include <stdio.h>
#include "testsuit.h"
#include "tools.h"

#define ARR_SIZE 8

void bubble_sort(int* array, size_t length)
{
    bool unsorted = true;
    for(size_t i = 0; i < length && unsorted; ++i){
        unsorted = false;
        for(size_t j = 1; j < length - i; ++j){
            if(array[j-1] > array[j]){
                unsorted = true;
                SWAP(array[j-1], array[j]);
            }
        }
    }
}

int main()
{
    int actual[ARR_SIZE] = { 4, 2, -1, 3, 24, 42, -5, 2 };
    int expected[ARR_SIZE] = { -5, -1, 2, 2, 3, 4, 24, 42 };
    bubble_sort(actual, ARR_SIZE);
    ASSERT_COLLECTION_EQUAL(expected, ARR_SIZE, actual, ARR_SIZE);

    printf("SUCCESS\nSorted Array: ");
    ARRAY_PRINT(actual, ARR_SIZE);
}

#include <stdio.h>
#include <assert.h>
#include "testsuit.h"
#include "tools.h"

#define ARR_SIZE 10

#define DEBUG

void _merge(int array[], size_t low, size_t middle, size_t high)
{
    size_t l, h, i;
    size_t tmp_size = high - low + 1;
    int tmp[tmp_size];

    for (i = 0, l = low, h = middle + 1; i < tmp_size; ++i) {
        if (l <= middle && (h > high || array[l] < array[h])) {
            tmp[i] = array[l++];
        } else {
            tmp[i] = array[h++];
        }
    }

    for (i = 0; i< tmp_size; ++i) {
        array[low+i] = tmp[i];
    }
}

void _merge_sort(int array[], const size_t low, const size_t high)
{
    if (low >= high) return; /* break recursion */

#ifdef DEBUG
    printf("--> [%zu...%zu]: ", low, high);
    ARRAY_PRINT(array + low, high - low + 1);
#endif

    size_t middle = low + (high - low) / 2; /* prevent potential memory overflow
                                             * of '(low + high) / 2' */
    _merge_sort(array, low, middle);
    _merge_sort(array, middle + 1, high);
    _merge(array, low, middle, high);

#ifdef DEBUG
    printf("<-- [%zu...%zu]: ", low, high);
    ARRAY_PRINT(array + low, high - low + 1);
#endif
}

void merge_sort(int array[], const size_t array_size)
{
    _merge_sort(array, 0, array_size - 1);
}

int main()
{
    float actual[ARR_SIZE] = { 4, 2, -1, 3, 24, 42, -5, 2, 66, 5 };
    float expected[ARR_SIZE] = { -5, -1, 2, 2, 3, 4, 5, 24, 42, 66 };
    merge_sort(actual, ARR_SIZE);
    ASSERT_COLLECTION_EQUAL(expected, ARR_SIZE, actual, ARR_SIZE);

    printf("SUCCESS\nSorted Array: ");
    ARRAY_PRINT(actual, ARR_SIZE);
    return 0;
}

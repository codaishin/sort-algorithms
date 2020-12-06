#include <stdio.h>
#include <string.h>
#include "array_tools.h"

#define DEBUG

void merge(int* array, size_t i_first, size_t i_middle, size_t i_last)
{
    size_t l, h, i;
    size_t tmp_size = i_last - i_first + 1;
    int tmp[tmp_size];

    for (i = 0, l = i_first, h = i_middle + 1; i < tmp_size; ++i) {
        if (l <= i_middle && (h > i_last || array[l] < array[h])) {
            tmp[i] = array[l++];
        } else {
            tmp[i] = array[h++];
        }
    }

    for (i = 0; i < tmp_size; ++i) {
        array[i_first+i] = tmp[i];
    }
}

void merge_sort(int* array, size_t i_first, size_t i_last)
{
    if (i_first >= i_last) return;


    size_t i_middle = i_first + (i_last - i_first) / 2;
    merge_sort(array, i_first, i_middle);
    merge_sort(array, i_middle + 1, i_last);

#ifdef DEBUG
    printf("--> [%zu...%zu]: ", i_first, i_last);
    arr_print(array + i_first, i_last - i_first + 1);
#endif

    merge(array, i_first, i_middle, i_last);

#ifdef DEBUG
    printf("<-- [%zu...%zu]: ", i_first, i_last);
    arr_print(array + i_first, i_last - i_first + 1);
#endif
}

void sort(int* array, size_t size)
{
    merge_sort(array, 0, size - 1);
}

int main()
{
    size_t index;
    size_t size = 10;
    int array[size];
    arr_random(array, size, 0, 99);
    arr_print(array, size);
    sort(array, size);
    if (!test_sorted(array, size, &index)) {
        printf("NOT SORTED!\n");
    }
    arr_print(array, size);
}

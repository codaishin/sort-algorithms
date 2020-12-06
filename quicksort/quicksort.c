#include <stdio.h>
#include "array_tools.h"

#define DEBUG

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

size_t partition_geeks4geeks(int* array, size_t left, size_t right)
{
    size_t l = left ? left - 1 : SIZE_MAX;
    int pivot_value = array[right];
    for (size_t r = left; r < right; ++r) {
        if (array[r] < pivot_value) {
            swap(&array[++l], &array[r]);
        }
    }
    swap(&array[++l], &array[right]);
    return l;
}

size_t partition(int* array, size_t left, size_t right)
{
    size_t l = left, r = right - 1;
    int pivot_value = array[right];
    while (l < r) {
        while (array[l] <= pivot_value && l < r) {
            ++l;
        }
        while (array[r] >= pivot_value && l < r) {
            --r;
        }
        if(l < r && array[l] > array[r]) {
            swap(&array[l], &array[r]);
        }
    }
    if(array[l] <= pivot_value) {
        ++l;
    }
    swap(&array[l], &array[right]);
    return l;
}

void quick_sort(int* array, size_t left, size_t right)
{
    if(left >= right) return;
    size_t pivot;

    static size_t i = 0;
    if(i++ > 10) return;

#ifdef DEBUG
    printf("--> [%zu...%zu]: ", left, right);
    arr_print(array + left, right - left + 1);
#endif

    // pivot = partition_geeks4geeks(array, left, right);
    pivot = partition(array, left, right);

#ifdef DEBUG
    printf("<-- [%zu.%zu.%zu]: ", left, pivot, right);
    arr_print(array + left, right - left + 1);
#endif

    quick_sort(array, left, pivot ? pivot - 1 : 0);
    quick_sort(array, pivot + 1, right);
}

void sort(int* array, size_t size)
{
    quick_sort(array, 0, size - 1);
}




size_t partition_new(int* array, size_t begin, size_t end)
{
    int pivot_value = array[end];
    size_t l = begin;
    size_t h = end ? end - 1 : 0;

    while (l < h) {
        if (array[l] > pivot_value) {
            while (array[h]> pivot_value) {
                --h;
            }
            if (l >= h) {
                swap(&array[l], &array[h]);
            }
        }
        ++l;
    }
    swap(&array[l], &array[end]);
    return l;
}

void quicksort_new(int* array, size_t begin, size_t end)
{
    if (begin >= end) return;

    size_t pivot = end;
    static size_t i = 0;
    printf("%zu\n", i++);

    printf("--> [%zu...%zu]: ", begin, end);
    arr_print(array + begin, end - begin + 1);

    pivot = partition_geeks4geeks(array, begin, end);

    printf("--> [%zu.%zu.%zu]: ", begin, pivot, end);
    arr_print(array + begin, end - begin + 1);

    quicksort_new(array, begin, pivot - 1);
    quicksort_new(array, pivot + 1, end);
}

void sort_new(int* array, size_t size)
{
    quicksort_new(array, 0, size ? size - 1 : 0);
}

int main()
{
    size_t size = 10;
    size_t index;
    int array[size];
    arr_random(array, size, 0, 99);
    arr_print(array, size);
    sort_new(array, size);
    if (!test_sorted(array, size, &index)) {
        printf("NOT SORTED!\nFirst error at index %zu\n", index);
    }
    arr_print(array, size);
}

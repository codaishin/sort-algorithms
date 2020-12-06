#include <stdio.h>
#include "array_tools.h"

void selection_sort(int* array, size_t size)
{
    int tmp;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (array[i] > array[j]) {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
}

void bubble_sort(int* array, size_t size)
{
    bool sorted = false;
    int tmp;
    size_t i, j;
    for (i = 0; i < size && sorted == false; ++i, ++count) {
        sorted = true;
        for (j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j+1]) {
                sorted = false;
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
}

int main()
{
    size_t size = 10;
    size_t index = 0;
    int array[size];
    arr_random(array, size, 0, 10);
    arr_ascending(array, size);
    printf("pre sort:  ");
    arr_print(array, size);
    // selection_sort(array, size);
    bubble_sort(array, size);
    if(test_sorted(array, size, &index)) {
        printf("sorted\n");
    } else {
        printf("UNSORTED\n");
    }
    printf("post sort: ");
    arr_print(array, size);
    return 0;
}
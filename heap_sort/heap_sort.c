#include <stdio.h>
#include "array_tools.h"

typedef enum {
    LEFT = 1,
    RIGHT = 2
} child_t;

void swap(int* a, int* b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}

bool child_index(child_t type, size_t index, size_t size, size_t* out)
{
    *out = index * 2 + type;
    return *out < size;
}

bool parent_index(size_t index, size_t* out)
{
    if (index > 0) {
        *out = (index - 1) / 2;
        return true;
    }
    return false;
}

void heap_print(int* array, size_t size)
{
    size_t width;
    size_t last;
    size_t i, j, k, l;
    int levels = 0;
    size_t offset = 0;
    bool healthy = true;

    for (last = 1, width = 1; last < size; last+=width) {
        width *= 2;
        ++levels;
        offset *= 2;
        ++offset;
    }

    for (i = 0, last = 0; i < size && healthy; --levels) {
        size_t branches = last < size ? last - i + 1 : size - i;
        if (i != 0) {
            for (j = 0; j < (branches + 2 - 1) / 2; ++j) {
                for (k = 0; k < 1; ++k) {
                    printf("  ");
                    for (l = 0; l < offset; ++l) {
                        printf("  ");
                    }
                    printf("┌");
                    for (l = 0; l < offset; ++l) {
                        printf("──");
                    }
                    printf("┘");
                    if (j < branches / 2) {
                        printf("└");
                        for (l = 0; l < offset; ++l) {
                            printf("──");
                        }
                        printf("┐");
                        for (l = 0; l < offset; ++l) {
                            printf("  ");
                        }
                        printf("  ");
                    }
                }

            }
        }
        putchar('\n');
        for (j = i; j <= last && j < size; ++j) {
            for (k = 0; k < offset; ++k) {
                printf("  ");
            }
            printf(" %02i ", array[j]);
            for (k = 0; k < offset; ++k) {
                printf("  ");
            }
            ++branches;
        }
        putchar('\n');
        if (!child_index(RIGHT, last, size, &last)) {
            last = size - 1;
        }
        --offset;
        offset /= 2;
        i = j;
    }
}

void heapify(int *array, size_t size)
{
    size_t parent;
    size_t current;
    for (size_t i = 0; i < size; ++i) {
        for (current = i; parent_index(current, &parent); current = parent) {
            if(array[current] > array[parent]) {
                swap(&array[current], &array[parent]);
            }
        }
    }
}

void de_heapify(int *heap, size_t size)
{
    size_t l_child;
    size_t r_child;
    size_t a_child;
    size_t current;
    size_t rest_size = size;
    for (size_t i = size - 1; i > 0; --i) {
        swap (&heap[i], &heap[0]);
        --rest_size;
        current = 0;
        while (child_index(LEFT, current, rest_size, &l_child)) {
            if (child_index(RIGHT, current, rest_size, &r_child)) {
                a_child = heap[l_child] > heap[r_child] ? l_child : r_child;
            } else {
                a_child = l_child;
            }
            if (heap[a_child] > heap[current]) {
                swap(&heap[a_child], &heap[current]);
            }
            current = a_child;
        }
    }
}

void sort(int* array, size_t size)
{
    heapify(array, size);
    heap_print(array, size);
    de_heapify(array, size);
    heap_print(array, size);
}

int main()
{
    size_t size = 15;
    int array[size];
    size_t index;
    arr_random(array, size, 0, 15);
    arr_print(array, size);
    sort(array, size);
    if(!test_sorted(array, size, &index)){
        printf("NOT SORTED\n");
    }
    arr_print(array, size);
    return 0;
}

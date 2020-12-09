#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    size_t count;
    char* fmt;
} meta_data_t;

int* imalloc(size_t size)
{
    meta_data_t* ptr = (meta_data_t*)malloc(sizeof(meta_data_t) + size * sizeof(int));
    ptr->size = size * sizeof(int);
    ptr->count = size;
    ptr->fmt = "%i ";
    return (int*)++ptr;
}

void ifree(int* array)
{
    if (array) {
        meta_data_t* ptr = (meta_data_t*)array;
        --ptr;
        free(ptr);
    }
}

char *array_fmt(int* array)
{
    meta_data_t* ptr = (meta_data_t*) array;
    --ptr;
    return ptr->fmt;
}

size_t array_size(int* array)
{
    meta_data_t* ptr = (meta_data_t*) array;
    --ptr;
    return ptr->size;
}

size_t array_count(int* array)
{
    meta_data_t* ptr = (meta_data_t*) array;
    --ptr;
    return ptr->count;
}

int* array_enlarge(int* array, size_t size)
{
    size_t old_size = array_count(array);
    meta_data_t* ptr = (meta_data_t*)array;
    --ptr;
    ptr = (meta_data_t*)realloc(ptr, sizeof(meta_data_t) + (old_size + size) * sizeof(int));
    ptr->size += (size * sizeof(int));
    ptr->count += size;
    return (int*)++ptr;
}

void array_print(int* array)
{
    for (size_t i = 0; i < array_count(array); ++i) {
        printf(array_fmt(array), array[i]);
    }
    printf("\n");
}

int main()
{
    int* array = imalloc(42);
    array_t array;

    array_print(array);
    printf("size: %zu\n", array_size(array));
    printf("count: %zu\n", array_count(array));

    array = array_enlarge(array, 8);
    array_print(array);
    printf("size: %zu\n", array_size(array));
    printf("count: %zu\n", array_count(array));

    ifree(array);
    return 0;
}
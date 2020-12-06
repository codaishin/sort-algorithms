#include <stdio.h>
#include <stdlib.h>

void array_fill(int begin_value, int* array, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        array[i] = begin_value++;
    }
}

void array_print(int* array, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        printf("%i ", array[i]);
    }
    printf("\n");
}

int main()
{
    size_t size = 10;
    size_t add_size = 5;
    int* array = malloc(size * sizeof(int));
    array_fill(0, array, size);
    array_print(array, size);
    array = realloc(array, sizeof(int) * (size + add_size));
    if (array) {
        array_fill(40, array + size, add_size);
        array_print(array, size + add_size);
        free(array);
    }
    return 0;
}

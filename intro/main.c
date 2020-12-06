#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define LEN 20
#define true 1
#define false 0
#define IS_OK(expr) (expr == true)

typedef uint8_t bool;
typedef enum error {
    ERROR = -1,
    SUCCESS,
    INVALID_BOUNDS,
} error_t;

char *error_to_string(error_t error)
{
    switch (error) {
        case ERROR:
            return "GENERAL ERROR (salute, you maggot)";
        case SUCCESS:
            return "SUCCESS";
        case INVALID_BOUNDS:
            return "INVALID_BOUNDS";
        default:
            return "UNKNOWN ERROR";
    }
}

void array_ascending(int* array, size_t size)
{
    for(size_t i = 0; i < size; ++i) {
        array[i] = i;
    }
}

error_t array_random(int* array, size_t size, int lower, int upper)
{
    if(lower >= upper) {
        return INVALID_BOUNDS;
    }
    for (size_t i = 0; i < size; ++i) {
        array[i] = rand() % (upper - lower - 1) + lower + 1;
    }
    return SUCCESS;
}

void array_print(int* array, size_t size)
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

int main()
{
    int array[LEN];
    size_t index = 0;
    array_ascending(array, LEN);
    array_random(array, LEN, 0, 10);
    if(IS_OK(test_sorted(array, LEN, &index))) {
        printf("array was sorted: ");
    } else {
        printf("array was !!NOT!! sorted, error at %zu: ", index);
    }
    array_print(array, LEN);
    return 0;
}

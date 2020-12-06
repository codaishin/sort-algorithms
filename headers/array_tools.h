#ifndef ARRAY_TOOLS_H
#define ARRAY_TOOLS_H

#include "tools.h"

char *error_to_string(error_t error);
void arr_ascending(int* array, size_t size);
error_t arr_random(int* array, size_t size, int lower, int upper);
void arr_print(int* array, size_t size);
bool test_sorted(int* array, size_t size, size_t* index_ptr);

#endif
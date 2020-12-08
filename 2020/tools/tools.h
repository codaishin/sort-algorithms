#ifndef TOOLS_H
#define TOOLS_H

#include <stdlib.h>

#define ASSERT_EQUAL(expected, actual, size) \
	assert_equal(expected, actual, size, __FUNCTION__)

#define ASSERT_STR_EQUAL(expected, actual, size) \
	assert_str_equal(expected, actual, size, __FUNCTION__)

void assert_equal(int* expected, int* actual, size_t size, const char* funcname);
void assert_str_equal(char** expected, char** actual, size_t size, const char* funcname);
void array_to_console(int* array, size_t size);
void str_array_to_console(char** array, size_t size);

#endif

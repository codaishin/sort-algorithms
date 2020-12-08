#ifndef TOOLS_H
#define TOOLS_H

#include <stdlib.h>

#define ASSERT_EQUAL(expected, actual, size) \
	assert_equal(expected, actual, size, __FUNCTION__)

void assert_equal(int* expected, int* actual, size_t size, const char* funcname);
void array_print(int* array, size_t size);

#endif

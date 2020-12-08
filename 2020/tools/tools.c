#include <stdio.h>
#include "tools.h"

void array_print(int* array, size_t size)
{
	printf("[");
	size_t i;
	for (i = 0; i < size - 1; ++i) {
		printf("%i, ", array[i]);
	}
	printf("%i]\n", array[i]);
}

void assert_equal(int* expected, int* actual, size_t size, const char* funcname)
{
	int okay = 1;
	for (size_t i = 0; i < size && okay; ++i) {
		if (expected[i] != actual[i]) {
			printf("[\033[0;31mX\033[0m] %s\n", funcname);
			printf(" ├─ expected: ");
			array_print(expected, size);
			printf(" └── but was: ");
			array_print(actual, size);
			okay = 0;
		}
	}
	if (okay) {
		printf("[\033[0;32m✓\033[0m] %s\n", funcname);
	}
}

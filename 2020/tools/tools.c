#include <stdio.h>
#include <string.h>
#include "tools.h"

#define BUFFSIZE 8

typedef struct {
	const char green[BUFFSIZE];
	const char red[BUFFSIZE];
	const char reset[BUFFSIZE];
} colors_t;

const colors_t colors = {
	green: "\033[0;32m",
	red: "\033[0;31m",
	reset: "\033[0m",
};

void array_to_console(int* array, size_t size)
{
	printf("[");
	size_t i;
	for (i = 0; i < size - 1; ++i) {
		printf("%i, ", array[i]);
	}
	printf("%i]\n", array[i]);
}

void str_array_to_console(char** array, size_t size)
{
	printf("[");
	size_t i;
	for (i = 0; i < size - 1; ++i) {
		printf("%s, ", array[i]);
	}
	printf("%s]\n", array[i]);
}

void assert_equal(int* expected, int* actual, size_t size, const char* funcname)
{
	int okay = 1;
	for (size_t i = 0; i < size && okay; ++i) {
		if (expected[i] != actual[i]) {
			printf("[%sX%s] %s\n", colors.red, colors.reset, funcname);
			printf(" ├─ expected: ");
			array_to_console(expected, size);
			printf(" └── but was: ");
			array_to_console(actual, size);
			okay = 0;
		}
	}
	if (okay) {
		printf("[%s✓%s] %s\n", colors.green, colors.reset, funcname);
	}
}

void assert_str_equal(char** expected, char** actual, size_t size, const char* funcname)
{
	int okay = 1;
	for (size_t i = 0; i < size && okay; ++i) {
		if (strcmp(expected[i], actual[i])) {
			printf("[%sX%s] %s\n", colors.red, colors.reset, funcname);
			printf(" ├─ expected: ");
			str_array_to_console(expected, size);
			printf(" └── but was: ");
			str_array_to_console(actual, size);
			okay = 0;
		}
	}
	if (okay) {
		printf("[%s✓%s] %s\n", colors.green, colors.reset, funcname);
	}
}

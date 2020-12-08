#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "tools.h"

/* forward declarations */
void sort(char** array, size_t size);


void order_one_char()
{
	char* array[4] = { "C", "A", "C", "B" };
	char* expceted[4] = { "A", "B", "C", "C" };

	sort(array, 4);

	ASSERT_STR_EQUAL(expceted, array, 4);
}


void order_two_chars()
{
	char* array[4] = { "CB", "AB", "CA", "BA" };
	char* expceted[4] = { "AB", "BA", "CA", "CB" };

	sort(array, 4);

	ASSERT_STR_EQUAL(expceted, array, 4);
}


void order_variable_chars()
{
	char* array[4] = { "CB1", "AB12", "CB", "B" };
	char* expceted[4] = { "AB12",  "B", "CB", "CB1" };

	sort(array, 4);

	ASSERT_STR_EQUAL(expceted, array, 4);
}


void run_tests()
{
	order_one_char();
	order_two_chars();
	order_variable_chars();
}


void update_counts(size_t* counts, char** array,
                   size_t size, size_t i_char)
{
	size_t tmp, i;
	for (i = 0; i < size; ++i) {
		tmp = strlen(array[i]) > i_char ? (size_t)array[i][i_char] : 0;
		++counts[tmp];
	}
	for (i = 1; i < CHAR_MAX; ++i) {
		counts[i] += counts[i-1];
	}
}


void update_buffer(char** buffer, size_t* counts, char** array,
                   size_t size, size_t i_char)
{
	size_t tmp, i = size;
	while(i--) {
		tmp = strlen(array[i]) > i_char ? (size_t)array[i][i_char] : 0;
		tmp = --counts[tmp];
		buffer[tmp] = array[i];
	}
}


size_t get_max_length(char** array, size_t size)
{
	size_t i, length, tmp;
	for (i = 0, length = 0; i < size; ++i) {
		tmp = strlen(array[i]);
		if (tmp > length) {
			length = tmp;
		}
	}
	return length;
}


void sort(char** array, size_t size)
{
	char* buff[size];
	size_t counts[CHAR_MAX];
	size_t length = get_max_length(array, size);

	while (length--) {
		memset(counts, 0, CHAR_MAX * sizeof(*counts));
		update_counts(counts, array, size, length);
		update_buffer(buff, counts, array, size, length);
		memcpy(array, buff, size * sizeof(*array));
	}
}


int main()
{
	run_tests();
	return 0;
}

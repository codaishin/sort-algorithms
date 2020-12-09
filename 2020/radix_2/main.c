#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "tools.h"

/* Forward Declarations */
void counters_count(int* counters, char** array, size_t size, size_t char_r_index);
void counters_to_buffer(int* counters, char** array, char**buff, size_t size, size_t char_r_index);
size_t get_max_length(char** array, size_t size);

void set_range(int* array, int value, size_t start, size_t count)
{
	for (size_t i = 0; i < count; ++i) {
		array[start+i] = value;
	}
}

void test_count_set_empty()
{
	int counters[CHAR_MAX];
	int expected[CHAR_MAX] = {0};  // empty expectation

	counters_count(counters, NULL, 0, 0);

	ASSERT_EQUAL(expected, counters, CHAR_MAX);
}

void test_count_r_index_0()
{
	char* array[] = { "A", "B", "A", "2" };
	int counters[CHAR_MAX];  // using ints, beacuse we have a ASSERT_EQUAL for that
	int expected[CHAR_MAX] = {0};

	set_range(expected, 1, '2', ('A' - '2'));
	set_range(expected, 3, 'A', ('B' - 'A'));
	set_range(expected, 4, 'B', (CHAR_MAX - 'B'));

	counters_count(counters, array, 4, 0);

	ASSERT_EQUAL(expected, counters, CHAR_MAX);
}

void test_count_r_index_1_lenght_2()
{
	char* array[] = { "_A", "_B", "_A", "_2" };
	int counters[CHAR_MAX];  // using ints, beacuse we have a ASSERT_EQUAL for that
	int expected[CHAR_MAX] = {0};

	set_range(expected, 1, '2', ('A' - '2'));
	set_range(expected, 3, 'A', ('B' - 'A'));
	set_range(expected, 4, 'B', (CHAR_MAX - 'B'));

	counters_count(counters, array, 4, 0);

	ASSERT_EQUAL(expected, counters, CHAR_MAX);
}

void test_count_r_index_1_variable_size()
{
	char* array[] = { "A1", "A2", "B", "A" };
	int counters[CHAR_MAX];  // using ints, beacuse we have a ASSERT_EQUAL for that
	int expected[CHAR_MAX] = {0};

	set_range(expected, 2, 0, ('A' - 0));
	set_range(expected, 4, 'A', (CHAR_MAX - 'A'));

	counters_count(counters, array, 4, 1);

	ASSERT_EQUAL(expected, counters, CHAR_MAX);
}

void test_counters_to_buffer()
{
	char* array[] = { "A", "B", "A", "2" };
	char* buff[] = { "", "", "", "" };
	char* expected[] = { "2", "A", "A", "B" };
	int counter[CHAR_MAX] = {0};

	set_range(counter, 1, '2', ('A' - '2'));
	set_range(counter, 3, 'A', ('B' - 'A'));
	set_range(counter, 4, 'B', (CHAR_MAX - 'B'));

	counters_to_buffer(counter, array, buff, 4, 0);

	ASSERT_STR_EQUAL(expected, buff, 4);
}

void test_counters_to_buffer_var_size()
{
	char* array[] = { "A1", "A2", "B", "A" };
	char* buff[] = { "", "", "", "" };
	char* expected[] = { "B", "A", "A1", "A2" };
	int counter[CHAR_MAX] = {0};

	set_range(counter, 2, 0, ('A' - 0));
	set_range(counter, 4, 'A', (CHAR_MAX - 'A'));

	counters_to_buffer(counter, array, buff, 4, 1);

	ASSERT_STR_EQUAL(expected, buff, 4);
}

void test_max_length()
{
	char* array[] = { "AA", "BBB", "AAAA", "" };
	size_t max_length = get_max_length(array, 4);

	if (max_length == 4) printf("[✓] test_max_length\n");
	else printf("[X] FAILE: expected: 4, but was: %zu\n", max_length);
}


void run_tests()
{
	test_count_set_empty();
	test_count_r_index_0();
	test_count_r_index_1_lenght_2();  // redundant to test 0? ... may be deleted?
	test_count_r_index_1_variable_size();
	test_counters_to_buffer();
	test_counters_to_buffer_var_size();
	test_max_length();
}


void counters_count(int* counters, char** array, size_t size, size_t char_r_index)
{
	size_t i, tmp;

	memset(counters, 0, CHAR_MAX * sizeof(*counters));

	for (i = 0; i < size; ++i) {
		tmp = strlen(array[i]);
		tmp = tmp > char_r_index ? array[i][tmp-char_r_index-1] : 0;
		++counters[tmp];
	}
	for (i = 1; i < CHAR_MAX; ++i) {
		counters[i] += counters[i-1];
	}
}

void counters_to_buffer(int* counters, char** array, char**buff, size_t size, size_t char_r_index)
{
	int i;
	size_t tmp;
	for (i = size - 1; i >= 0; --i) {
		tmp = strlen(array[i]);
		tmp = tmp > char_r_index ? array[i][tmp-char_r_index-1] : 0;
		tmp = --counters[tmp];
		buff[tmp] = array[i];
	}
}

size_t get_max_length(char** array, size_t size)
{
	size_t tmp, max, i;
	for (i = 0, max = 0; i < size; ++i) {
		tmp = strlen(array[i]);
		if (tmp > max) max = tmp;
	}
	return max;
}


void sort(char** array, size_t size)
{
	size_t length = get_max_length(array, size);
	char* buff[size];
	int counters[CHAR_MAX];

	for (size_t r = 0; r < length; ++r) {
		counters_count(counters, array, size, r);
		counters_to_buffer(counters, array, buff, size, r);
		memcpy(array, buff, size * sizeof(*array));
	}
}


int main()
{
	run_tests();

	char* strings[] = { "a", "world", "alf", "hello" };
	size_t size = sizeof(strings) / sizeof(*strings);

	sort(strings, size);

	str_array_to_console(strings, size);
}

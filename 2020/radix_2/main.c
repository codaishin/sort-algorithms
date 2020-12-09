#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "tools.h"

/* Forward Declarations */
void counters_count(int* counters, char** array, size_t size, size_t index);

void test_count_set_empty()
{
	int counters[CHAR_MAX];
	int expected[CHAR_MAX] = {0};  // empty expectation

	counters_count(counters, NULL, 0, 0);

	ASSERT_EQUAL(expected, counters, CHAR_MAX);
}

void test_count_index_0()
{
	char* array[] = { "A", "B", "A", "2" };
	int counters[CHAR_MAX];  // using ints, beacuse we have a ASSERT_EQUAL for that
	int expected[CHAR_MAX] = {0};
	expected[(int)'A'] = 2;
	expected[(int)'B'] = 1;
	expected[(int)'2'] = 1;

	counters_count(counters, array, 4, 0);

	ASSERT_EQUAL(expected, counters, CHAR_MAX);
}


void run_tests()
{
	test_count_set_empty();
	test_count_index_0();
}


void counters_count(int* counters, char** array, size_t size, size_t index)
{
	//size_t i = 0;

	memset(counters, 0, CHAR_MAX * sizeof(*counters));
}


int main()
{
	run_tests();
}

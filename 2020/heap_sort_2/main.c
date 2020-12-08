#include "tools.h"
#include <stdlib.h>

#define SWAP(a, b) \
	do { \
		int t = a; \
		a = b; \
		b = t; \
	} while(0)

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void heapify(int* array, size_t size)
{
	SWAP(array[0], array[1]);
}

/* tests */
void test_heap_two_items()
{
	int array[] = { 1, 2 };
	int expected[] = { 2, 1 };

	heapify(array, 2);

	ASSERT_EQUAL(expected, array, 2);
}

void run_tests()
{
	test_heap_two_items();
}
/* tests over */

int main()
{
	run_tests();
	return 0;
}

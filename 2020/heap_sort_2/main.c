#include "tools.h"
#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b) \
	do { \
		__typeof__(a) t= a; \
		a = b; \
		b = t; \
	} while(0)

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

size_t prnix(size_t chi)
{
	return (chi - 1) / 2;
}

void heapify(int* array, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		size_t p = prnix(i);
		if (i > 0 && array[p] < array[i]) {
			SWAP(array[p], array[i]);
		}
	}
}

/* tests */
void test_heap_2_items()
{
	int array[] = { 1, 2 };
	int expected[] = { 2, 1 };

	heapify(array, 2);

	ASSERT_EQUAL(expected, array, 2);
}

void test_heap_2_items_no_swap()
{
	int array[] = { 2, 1 };
	int expected[] = { 2, 1 };

	heapify(array, 2);

	ASSERT_EQUAL(expected, array, 2);
}

void test_heap_3_items()
{
	int array[] = { 1, 2, 3 };
	int expected[] = { 3, 1, 2 };

	heapify(array, 3);

	ASSERT_EQUAL(expected, array, 3);
}

void test_heap_4_items()
{
	int array[] = { 3, 1, 2, 4 };
	int expected[] = { 4, 3, 2, 1 };

	/**
	 *     3
	 *   1   2
	 * 4
	 *
	 *     3
	 *   4   2
	 * 1
	 *
	 *     4
	 *   3   2
	 * 1
	 */

	heapify(array, 4);

	ASSERT_EQUAL(expected, array, 4);
}

void run_tests()
{
	test_heap_2_items();
	test_heap_2_items_no_swap();
	test_heap_3_items();
	test_heap_4_items();
}
/* tests over */

int main()
{
	run_tests();
	return 0;
}

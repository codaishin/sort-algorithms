#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SWAP(a, b) \
	do { \
		__typeof__(a) t = a; \
		a = b; \
		b = t; \
	} while(0)

size_t prnix(size_t chi)
{
	return (chi - 1) / 2;
}

size_t lchix(size_t prn)
{
	return (prn * 2) + 1;
}

size_t rchix(size_t prn)
{
	return (prn * 2) + 2;
}

void sort_up(int* array, size_t index)
{
	size_t parent = prnix(index);
	size_t current = index;
	while (current > 0 && array[parent] < array[current]) {
		SWAP(array[parent], array[current]);
		current = parent;
		parent = prnix(current);
	}
}

void heapify(int* array, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		sort_up(array, i);
	}
}

bool get_child(int* heap, size_t size, size_t current, size_t* child)
{
	size_t lchild = lchix(current);
	size_t rchild = rchix(current);
	bool rc = false;

	if (rchild < size) {
		*child = heap[lchild] > heap[rchild] ? lchild : rchild;
		rc = true;
	} else if (lchild < size) {
		*child = lchild;
		rc = true;
	}
	return rc;
}

void sort_down(int* heap, size_t size)
{
	size_t current = 0;
	size_t child;

	while (get_child(heap, size, current, &child) && heap[current] < heap[child]) {
		SWAP(heap[current], heap[child]);
		current = child;
	}
}

void deheapify(int* heap, size_t size)
{
	for (size_t i = size - 1; i > 0; --i) {
		SWAP(heap[0], heap[i]);
		sort_down(heap, i);
	}
}

#define TEST 1

#if TEST

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

	heapify(array, 4);

	ASSERT_EQUAL(expected, array, 4);
}

void test_unheap_2_items()
{
	int array[] = { 2, 1 };
	int expected[] = { 1, 2 };

	deheapify(array, 2);

	ASSERT_EQUAL(expected, array, 2);
}

void test_unheap_3_items()
{
	int array[] = { 3, 1, 2 };
	int expected[] = { 1, 2, 3 };

	deheapify(array, 3);

	ASSERT_EQUAL(expected, array, 3);
}

void test_unheap_4_items()
{
	int array[] = { 4, 3, 2, 1 };
	int expected[] = { 1, 2, 3, 4 };

	deheapify(array, 4);

	ASSERT_EQUAL(expected, array, 4);
}

void test_unheap_4_items_right_bigger()
{
	int array[] = { 4, 2, 3, 1 };
	int expected[] = { 1, 2, 3, 4 };

	deheapify(array, 4);

	ASSERT_EQUAL(expected, array, 4);
}

void run_tests()
{
	test_heap_2_items();
	test_heap_2_items_no_swap();
	test_heap_3_items();
	test_heap_4_items();
	test_unheap_2_items();
	test_unheap_3_items();
	test_unheap_4_items();
	test_unheap_4_items_right_bigger();
}

#endif

void sort(int* array, size_t size)
{
	heapify(array, size);
	deheapify(array, size);
}

int main()
{
	#if TEST
	run_tests();
	#else
	int array[] = { 2, -4, 10, 9, 66, 25, 9, 5, 2, 3, 10, -98, 22, 54, 42, 10 };
	size_t size = sizeof(array) / sizeof(*array);

	array_to_console(array, size);

	sort(array, size);

	array_to_console(array, size);
	#endif


	return 0;
}

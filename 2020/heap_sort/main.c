#include <stdio.h>

#define SWAP(a, b) \
	{ \
		__typeof__(a) t = a; \
		a = b; \
		b = t; \
	} while(0)

size_t lchix(size_t prn)
{
	return prn * 2 + 1;
}

size_t rchix(size_t prn)
{
	return prn * 2 + 2;
}

size_t prnix(size_t chi)
{
	return (chi - 1) / 2;
}

void array_print(int* array, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		printf("%i ", array[i]);
	}
	printf("\n");
}

void sort_up(int* heap, size_t index)
{
	size_t parent = prnix(index);
	while (index > 0 && heap[index] > heap[parent]) {
		SWAP(heap[index], heap[parent]);
		index = parent;
		parent = prnix(index);
	}
}

void heapify(int* array, size_t size)
{
	for (size_t i = 1; i < size; ++i) {
		sort_up(array, i);
	}
}

int main()
{
	int array[8] = { 6, 5, 3, 1, 8, 7, 2, 4 };

	heapify(array, 8);

	array_print(array, 8); // { 8, 6, 7, 4, 5, 3, 2, 1 }
}

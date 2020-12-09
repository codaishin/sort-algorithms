#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tools.h"

#define SWAP(a, b) { \
		__typeof__(a) t = a; \
		a = b; \
		b = t; \
	} while(0)


size_t partition(int *array, size_t size)
{
	long int p = size - 1;
	long int l = 0, r = p - 1;


	while (l < r) {
		while (array[l] < array[p]) {
			++l;
		}
		while (array[r] >= array[p]) {
			--r;
		}
		if (l < r) {
			SWAP(array[l], array[r]);
		}
	}
	SWAP(array[l], array[p]);
	return l;
}


void sort(int* array, size_t size)
{
	if (!size) return;

	size_t pivot = partition(array, size);
	sort(array, pivot++);
	sort(array + pivot, size - pivot);
}


void init_random(int* array, size_t size, int range)
{
	srand(time(NULL));

	for (size_t i = 0; i < size; ++i) {
		array[i] = rand() % range;
	}
}


int main()
{
	size_t size = 20;
	int array[size];

	init_random(array, size, 20);

	array_to_console(array, size);

	sort(array, size);

	array_to_console(array, size);
	return 0;
}

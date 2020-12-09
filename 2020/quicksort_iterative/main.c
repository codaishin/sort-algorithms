#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tools.h"


#define SWAP(a, b) { \
		__typeof__(a) t = a; \
		a = b; \
		b = t; \
	} while(0)


size_t partition(int *array, size_t fst, size_t lst)
{
	long int p = lst;
	long int l = fst, r = p - 1;

	while (l <= r) {
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
	long int i = 0;
	size_t buff[size];
	size_t l, r, p;
	buff[i++] = 0;
	buff[i++] = size - 1;

	while (i > 0) {
		r = buff[--i];
		l = buff[--i];
		p = partition(array, l, r);
		if (p > l) {
			buff[i++] = l;
			buff[i++] = p - 1;
		}
		if (r > p) {
			buff[i++] = p + 1;
			buff[i++] = r;
		}
	}
}


void init_random(int* array, size_t size, int range)
{
	srand(time(NULL));

	for (size_t i = 0; i < size; ++i) {
		array[i] = rand() % range;
	}
}


#define SIZE 10


int main()
{
	int array[SIZE];

	init_random(array, SIZE, 20);

	array_to_console(array, SIZE);

	sort(array, SIZE);

	array_to_console(array, SIZE);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void array_print(int* array, size_t size)
{
	for (int i = 0; i < size; ++i) {
		printf("%i ", array[i]);
	}
	printf("\n");
}

void array_merge_part(int* array, size_t middle, size_t size)
{
	int tmp[size];
	size_t i, left, right;
	for (i = 0, left = 0, right = middle; i < size; ++i) {
		if (left >= middle) {
			tmp[i] = array[right++];
		} else if (right >= size) {
			tmp[i] = array[left++];
		} else {
			tmp[i] = array[left] < array[right] ? array[left++] : array[right++];
		}
	}
	for (i = 0; i < size; ++i) {
		array[i] = tmp[i];
	}
}

void array_sort(int* array, size_t size)
{
	if (size < 2) return;

	size_t middle = size / 2;
	array_sort(array, middle);
	array_sort(array + middle, size - middle);

	array_merge_part(array, middle, size);
}

void array_init_rand(int*  array, size_t size, int range)
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

	array_init_rand(array, size, 100);

	array_print(array, size);
	array_sort(array, size);
	array_print(array, size);

	return 0;
}

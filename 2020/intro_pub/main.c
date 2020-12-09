#include <stdio.h>

void array_print(int* array, size_t size)
{
	for (int i = 0; i < size; ++i) {
		printf("%i ", array[i]);
	}
	printf("\n");
}

void array_sort(int* array, size_t size)
{
	for (int h = 0; h < size; ++h) {
		for (int i = 1; i < size - h; ++i) {
			if (array[i-1] > array[i]) {
				int tmp = array[i-1];
				array[i-1] = array[i];
				array[i] = tmp;
			}
		}
	}
}

int main()
{
	int array[10] = {2, 3, 1, 4, 6, 10, -4, 9, 0, -100};

	array_sort(array, 10);
	array_print(array, 10);

	return 0;
}

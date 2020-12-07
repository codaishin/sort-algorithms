#include <stdio.h>
#include <stdint.h>

# define true 1
# define false 0

typedef uint8_t bool;

#define SWAP(a, b) \
	do { \
		int tmp = a; \
		a = b; \
		b = tmp; \
	} while(0)

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

bool array_is_ascending(int *array, size_t size)
{
	for (int i = 1; i < size; ++i) {
		if (array[i] < array[i-1]) {
			return false;
		}
	}
	return true;
}

void array_to_string(int *array, size_t size,
                     char* buffer, size_t buff_size)
{
	int i, j;
	for (i = 0, j = 0; i < size; ++i) {
		j += snprintf(buffer + j, buff_size - j, "%i, ", array[i]);
	}
	buffer[j-2] = '\0';
}

void array_sort(int *array, size_t size)
{
	for (int i = 0; i < size; ++i) {
		for (int j = 1; j < size - i; ++j) {
			if (array[j] < array[j-1]) {
				//swap(&(array[j]), &(array[j-1]));
				SWAP(array[j], array[j-1]);
			}
		}
	}
}

int main()
{
	int strlen = 128;
	int arraylen = 7;
	char string[strlen];
	int array[] = {1, 2, 1, 5, 3, 10, -8};

	array_sort(array, arraylen);
	array_to_string(array, arraylen, string, strlen);
	if (array_is_ascending(array, arraylen)) printf("Sorted!\n");
	else printf("Not sorted\n");
	printf("%s\n", string);
}

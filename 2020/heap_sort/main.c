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

void heapify(int* array, size_t size)
{
	size_t ia, ic, ip;
	for (ia = 0; ia < size; ++ia) {
		ic = ia;
		ip = prnix(ic);
		while (ic > 0 && array[ic] > array[ip]) {
			SWAP(array[ic], array[ip]);
			ic = ip;
			ip = prnix(ic);
		}
	}
}

int main()
{
	int array[8] = { 6, 5, 3, 1, 8, 7, 2, 4 };

	heapify(array, 8);

	array_print(array, 8); // { 8, 6, 7, 4, 5, 3, 2, 1 }
}

#include <stdio.h>


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

int main()
{
	int array[] = { 1, 2, 3, 4, 5, 6 };

	size_t prn = 5;

	printf("%zu\n", lchix(prn)); // => 7
	printf("%zu\n", rchix(prn)); // => 8
	printf("%zu\n", prnix(prn)); // => 1
}

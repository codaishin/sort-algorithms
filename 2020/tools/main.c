#include "tools.h"

void test_equality()
{
	int expected[] = { 1, 2, 3 };
	int actual[] = { 1, 5, 3 };

	ASSERT_EQUAL(expected, actual, 3);
}

int main()
{
	test_equality();

	return 0;
}

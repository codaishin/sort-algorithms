# search-algorithms
## Install Prepared libraries
```console
> cd tools
> make && make install
> cd ../testsuit
> make && make install
> cd ../array_tools
> make && make install
```


## Example main

```c
#include <stdio.h>
#include "testsuit.h"
#include "tools.h"

#define ARR_SIZE 8

void sort(int* array, size_t length)
{
    /* Implementation */
}

int main()
{
	/* Init variables */
	int actual[ARR_SIZE] = { 4, 2, -1, 3, 24, 42, -5, 2 };
	int expected[ARR_SIZE] = { -5, -1, 2, 2, 3, 4, 24, 42 };

	/* Call sort function */
	sort(actual, ARR_SIZE);

	/* Test equality */
	ASSERT_COLLECTION_EQUAL(expected, ARR_SIZE, actual, ARR_SIZE);

	/* Print success */
	printf("SUCCESS\nSorted Array: ");
	ARRAY_PRINT(actual, ARR_SIZE, ", ");
}
```

## Compile
### Manually
```console
> gcc bubble_sort.c -std=c99 -Wall -I../headers \
                    -L../lib -ltestsuit -ltools \
                    -Wl,-rpath=../lib -o bubble_sort.out
```
### Makefile
#### Setup
```console
cp ../makefile_template .
mv makefile_template makefile
```
Change `APPNAME` in makefile to your application name (must match the .c file)
```Makefile
APPNAME = bubble_sort
ROOT = ../

...
```
#### Usage
```console
> make
```

## Example Success Output
```console
> ./bubble_sort.out
SUCCESS
Sorted Array: -5,-1,2,2,3,4,24,42
```

## Example Failed Output
```console
> ./bubble_sort2.out
-5 == 2 FAILED
└── CONCRETE_VALUE missmatch
    ├── 1st: expected at index 0 = -5
    └── 2nd: actual at index 0 = 2
-1 == -5 FAILED
└── CONCRETE_VALUE missmatch
    ├── 1st: expected at index 1 = -1
    └── 2nd: actual at index 1 = -5
2 == -1 FAILED
└── CONCRETE_VALUE missmatch
    ├── 1st: expected at index 2 = 2
    └── 2nd: actual at index 2 = -1
---
expected == actual FAILED
├── 1st: expected: -5,-1,2,2,3,4,24,42
└── 2st: actual: 2,-5,-1,2,3,4,24,42
Aborted (core dumped)
```

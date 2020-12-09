#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
// #include "tools.h"
// #include "testsuit.h"

// typedef struct timeval time_ptr_t;

// bool is_prime(int value, int* known, size_t size)
// {
//     size_t i;
//     bool prime = true;
//     int divisor = 0;

//     if (value < 2 || value == 4) {
//         prime = false;
//     } else if (value != 2) {
//         for (i = 0; i < size && prime && divisor < value / 2; ++i) {
//             divisor = known[i];
//             if (value % divisor == 0) {
//                 prime = false;
//             }
//         }
//     }
//     return prime;
// }

// void primes(int *buff, int first, int last, int** primes, size_t *primes_count)
// {
//     int value;
//     size_t offset = 0;
//     *primes_count = 0;
//     for (value = 0; value <= last; ++value) {
//         if (value == 2 || is_prime(value, buff, *primes_count)) {
//             buff[(*primes_count)++] = value;
//             if (value < first) {
//                 ++offset;
//             }
//         }
//     }
//     *primes = buff + offset;
//     *primes_count -= offset;
// }

// void primes_forward(int *buff, int first, int last,
//                     int** primes, size_t *primes_count)
// {
//     bool *numbers = malloc((last + 1) * sizeof(bool));
//     size_t i, j, offset;
//     int value;

//     offset = 0;
//     *primes_count = 0;

//     memset(numbers, true, last + 1);
//     for (i = 2; i <= last; ++i) {
//         for(j = 2 * i; j <= last; j+=i) {
//             numbers[j] = false;
//         }
//     }

//     for (value = 2; value <= last; ++value) {
//         if(numbers[value] == true) {
//             buff[(*primes_count)++] = value;
//             if (value < first) {
//                 ++offset;
//             }
//         }
//     }
//     *primes = buff + offset;
//     *primes_count -= offset;
//     free(numbers);
// }

// int* allign_primes(int *array, size_t time_start)
// {
//     size_t allignment;
//     for (allignment = 0; array[allignment] < time_start; ++allignment);
//     return array + allignment;
// }

// double timediff(time_ptr_t* start, time_ptr_t* stop) {
//     return (double)(stop->tv_usec - start->tv_usec) / 1000000 +
//            (double)(stop->tv_sec - start->tv_sec);
// }

// int main()
// {
//     size_t first = 0;
//     size_t last = 99;
//     size_t max_count = last + 1;
//     size_t result_count;
//     time_ptr_t time_start[1];
//     time_ptr_t time_stop[1];
//     int *result_buff;
//     int *buff = malloc(max_count * sizeof(int));
//     int expected[] = {
//         2, 3, 5, 7, 11, 13, 17,
//         19, 23, 29, 31, 37, 41,
//         43, 47, 53, 59, 61, 67,
//         71, 73, 79, 83, 89, 97
//     };

//     gettimeofday(time_start, NULL);
//     // primes(buff, first, last, &result_buff, &result_count);
//     primes_forward(buff, first, last, &result_buff, &result_count);
//     gettimeofday(time_stop, NULL);

//     if (max_count <= 100) {
//         ASSERT_COLLECTION_EQUAL(
//             allign_primes(expected, first), result_count,
//             result_buff, result_count
//         );
//     }

//     ARRAY_PRINT(result_buff, result_count, "\n");
//     printf("Time to collect prime numbers: %f seconds\n", timediff(time_start, time_stop));
//     free(buff);
//     return 0;
// }

int is_prime(int value)
{
    for (int i = 2; i <= value / 2; ++i) {
        if (value % i == 0) {
            return 0;
        }
    }
    return 1;
}

int prime(int *array, size_t size, int min, int max)
{
    int counter = 0;
    int i;
    if (min < 2) {
        i = 2;
    } else {
        i = min;
    }
    for (; i <= max; ++i) {
        if (is_prime(i)) {
            array[counter] = i;
            ++counter;
        }
    }
    return counter;
}


int main()
{
    int min = 0;
    int max = 10000;
    size_t size = max - min + 1;
    size_t counter = 0;
    int array[size];
    double time;

    time = clock();
    counter = prime(array, size, min, max);
    time = (clock() - time) / CLOCKS_PER_SEC;

    for (size_t i = 0; i < counter; ++i) {
        printf("%i ", array[i]);
    }
    printf("\n");
    printf("elapsed: %f sec\n", time);
}

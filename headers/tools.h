#ifndef TOOLS_H
#define TOOLS_H

#include <stdint.h>

#define true 1
#define false 0

#define ISOK(test) (test == 0)

/**
 * @brief  Return corresponding variable_t to a variable
 * @note   Only works with variable defined in variable_t.
 * @param  x: Variable to return variable_t of.
 * @retval Corresponding variable_t.
 */
#define T2V_T(x) _Generic(x, \
    int:     INT, \
    float:   FLOAT, \
    double:  DOUBLE, \
    char:    CHAR, \
    void*:   VOIDP, \
    default: UNDEF)

#define ARRAY_PRINT(array, array_size, delim) \
    array_print((char*)(array), array_size, sizeof(*(array)), T2V_T(*(array)), delim)

typedef uint8_t bool;
typedef enum error
{
    ERROR = -1,
    SUCCESS = 0,
    TEST_FAILED,
    BUFFER_INSUFFICIENT,
    INVALID_BOUNDS,
} error_t;

typedef enum {
    UNDEF,
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    VOIDP,
} variable_t;

/**
 * @brief  Get string representation of an error_t variable.
 * @param  error: Error to be stringified.
 * @retval String literal.
 */
char *error_to_string(error_t error);

/**
 * @brief  Get string representation of a variable_t variable.
 * @param  type: Variable type var.
 * @retval String literal.
 */
char* type_to_string(const variable_t type);

#define SWAP(a, b) \
    do{ \
        __typeof__(a) tmp = a; \
        a = b; \
        b = tmp; \
    } while(0)


void array_print(char *array, const size_t array_size,
                 const size_t type_size, const variable_t type, char* delim);

/**
 * @brief  Store integer array on a string buffer.
 * @note   String buffer must be allocated before call.
 * @param  array: Array to be printed.
 * @param  array_size: Size of array
 * @param  buff: String buffer to store array information.
 * @param  buff_size: Size of string buffer.
 * @retval SUCCESS if operation worked, else according error.
 */
error_t array_to_string(int* array, size_t array_size,
                        char* buff, size_t buff_size);

#endif
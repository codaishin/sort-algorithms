#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "tools.h"


char *error_to_string(error_t error)
{
    switch (error) {
        case SUCCESS:
            return "SUCCESS";
        case ERROR:
            return "ERROR";
        case TEST_FAILED:
            return "TEST_FAILED";
        case BUFFER_INSUFFICIENT:
            return "BUFFER_INSUFFICIENT";
        default:
            return "UNKNOWN";
    }
}

char* type_to_string(const variable_t type)
{
    switch (type) {
        case INT:
            return "int";
        case FLOAT:
            return "float";
        case DOUBLE:
            return "double";
        case CHAR:
            return "char";
        case VOIDP:
            return "void*";
        case UNDEF:
            return "unknown type";
    }
    return "unknown type";
}

error_t array_to_string(int* array, size_t array_size, 
                        char* buff, size_t buff_size)
{
    error_t error = SUCCESS;
    int written = 0;

    if(buff_size < 3) {
        error = BUFFER_INSUFFICIENT;
    } else {
        buff[0] = '[';
        if (array_size == 0) {
            buff[1] = ']';
            buff[2] = '\0';
        } else {
            ++buff;
            --buff_size;
            for (size_t i = 0; i < array_size && ISOK(error); ++i){
                written = snprintf(buff, buff_size, "%i,", array[i]);
                if (written == -1) {
                    error = ERROR;
                } else if (buff_size < written){
                    error = BUFFER_INSUFFICIENT;
                } else {
                    buff_size -= written;
                    buff += written;
                }
            }
            if (ISOK(error)) buff[-1] = ']';
        }
    }
    return error;
}


#define PRINT(fmt, array, array_size, type, delim) \
    do { \
        if (array_size > 1 && i < array_size - 1) { \
            printf(fmt, *(type*)array); \
            printf("%s", delim); \
        } else { \
            printf(fmt, *(type*)array); \
        } \
    } while(0)


void array_print(char *array, const size_t array_size,
                 const size_t type_size, const variable_t type, char* delim)
{
    for (size_t i = 0; i < array_size; ++i, array+=type_size)
    {
        switch (type) {
            case INT:
                PRINT("%i", array, array_size, int, delim);
                break;
            case FLOAT:
                PRINT("%f", array, array_size, float, delim);
                break;
            case DOUBLE:
                PRINT("%f", array, array_size, double, delim);
                break;
            case CHAR:
                PRINT("%c", array, array_size, char, delim);
                break;
            case VOIDP:
                PRINT("%p", array, array_size, void*, delim);
                break;
            case UNDEF:
                if (array_size > 1 && i < array_size - 1) {
                    printf("%s%s", "type undefined", delim);
                } else {
                    printf("%s", "type undefined");
                }
                break;
        }
    } 
    printf("\n");
}

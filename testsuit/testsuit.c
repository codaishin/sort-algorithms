#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "testsuit.h"

#define STR_SIZE 256

#define BASE_FMT "%s %s %s FAILED\n" \
                 "└── %s missmatch\n"
#define SUB_FMT  "    ├── 1st: %s = %s\n" \
                 "    └── 2nd: %s = %s\n"
#define SIZE_FMT "%zu"
#define EQ "=="

#define TEST_TYPE(args, type, fmt, success) \
    do { \
        type a = *va_arg(args, type*); \
        type b = *va_arg(args, type*); \
        if(!APPLY_OP(op, a, b)) { \
            PRINT_FAIL(op, CONCRETE_VALUE, fmt, name_a, name_b, buff, a, b); \
            success = false; \
        } \
    } while(0)

#define OP_FLAGGED(operation, flag) \
    (flag & operation ? true : false)

#define APPLY_OP(op, a, b) \
    ((OP_FLAGGED(op, OP_E) ? a == b : false) || \
     (OP_FLAGGED(op, OP_GT) ? a > b : false) || \
     (OP_FLAGGED(op, OP_LT) ? a < b : false))

#define PRINT_FAIL(op, fail, fmt, name_a, name_b, buff, a, b) \
    do { \
        assert_written_ok( \
            snprintf( \
                buff, STR_SIZE, BASE_FMT SUB_FMT, \
                fmt, operation_to_string(op), fmt, fail_to_string(fail), \
                name_a, fmt, name_b, fmt \
            ), \
            STR_SIZE\
        );\
        printf(buff, a, b, a, b); \
    } while(0)

typedef uint8_t bool;
typedef enum {
    FAIL_NONE = 0,
    MEMORY_SIZE,
    CONCRETE_VALUE,
} fail_t;

char *fail_to_string(fail_t fail)
{
    switch (fail) {
        case FAIL_NONE:
            return "FAIL_NONE";
        case MEMORY_SIZE:
            return "MEMORY_SIZE";
        case CONCRETE_VALUE:
            return "CONCRETE_VALUE";
    }
    return "UNKNOWN";
}

char *operation_to_string(op_t operation)
{
    switch ((int)operation){
        case OP_E:
            return EQ;
        case OP_GT:
            return ">";
        case OP_LT:
            return "<";
        case (OP_GT | OP_E):
            return ">=";
        case (OP_LT | OP_E):
            return "<=";
        default:
            return "??";
    }
}

void assert_written_ok(int written, int buffer_size)
{
    if (written == -1){
        printf("WRITING IN TEST ASSERTION FAILED (ENCODING ERROR)\n");
        abort();
    }
    if (written >= STR_SIZE) {
        printf("WRITING IN TEST ASSERTION FAILED (BUFFER SIZE TOO SMALL)\n");
        abort();
    }
}

void assert_size(const char* name_a, const size_t size_a,
                 const char* name_b, const size_t size_b)
{
    char buff[STR_SIZE];
    if (size_a != size_b) {
        PRINT_FAIL(
            OP_E, MEMORY_SIZE, "%zu",
            name_a, name_b, buff, size_a, size_b
        );
        abort();
    }
}

void assert_type(const variable_t type_a, const variable_t type_b,
                 const char *fmt, const char* name_a, const char* name_b)
{
    if (type_a != type_b) {
        char buff_a[STR_SIZE];
        char buff_b[STR_SIZE];
        assert_written_ok(snprintf(buff_a, STR_SIZE, fmt, name_a), STR_SIZE);
        assert_written_ok(snprintf(buff_b, STR_SIZE, fmt, name_b), STR_SIZE);
        printf(BASE_FMT, name_a, "==", name_b, "TYPE MISSMATCH");
        printf(
            SUB_FMT, 
            buff_a, type_to_string(type_a),
            buff_b, type_to_string(type_b)
        );
        abort();
    }
}

bool compare(op_t op, const char* name_a, const char* name_b,
             const variable_t type, const bool abort_on_fail, ...)
{
    char buff[STR_SIZE];
    bool success = true;
    va_list args;
    va_start(args, abort_on_fail);
    switch (type) {
        case INT: {
            TEST_TYPE(args, int, "%i", success);
            break;
        }
        case FLOAT: {
            TEST_TYPE(args, float, "%f", success);
            break;
        }
        case DOUBLE: {
            TEST_TYPE(args, double, "%f", success);
            break;
        }
        case CHAR: {
            TEST_TYPE(args, char, "%c", success);
            break;
        }
        case VOIDP: {
            TEST_TYPE(args, void*, "%p", success);
            break;
        }
        case UNDEF:
            printf(
                "COMPARISON IN TEST ASSERTION FAILED "
                "(%s BEHAVIOUR NOT DEFINED)\n",
                type_to_string(type)
            );
            success = false;
            break;
    }
    va_end(args);
    if(success == false && abort_on_fail) abort();
    return success;
}

bool assert_op(op_t op, 
               const void* ptr_a, const size_t size_a, 
               const variable_t type_a, const char* name_a,
               const void* ptr_b, const size_t size_b,
               const variable_t type_b, const char* name_b,
               const bool abort_on_fail)
{
    assert_type(type_a, type_b, "typeof(%s)", name_a, name_b);
    if (size_a != size_b) {
        char buff[STR_SIZE];
        PRINT_FAIL(
            OP_E, MEMORY_SIZE, "%zu",
            name_a, name_b, buff, size_a, size_b
        );
        if (abort_on_fail) abort();
        return false;
    }
    return compare(op, name_a, name_b, type_a, abort_on_fail, ptr_a, ptr_b);
}

void assert_collection_equal(void* a, const size_t size_a, 
                             const variable_t type_a, const char* name_a,
                             void* b, const size_t size_b,
                             const variable_t type_b, const char* name_b,
                             size_t type_size)
{
    bool success = true;
    bool tmp = success;
    char* ptr_a = a;
    char* ptr_b = b;
    char buff_a[STR_SIZE];
    char buff_b[STR_SIZE];
    assert_size(name_a, size_a, name_b, size_b);
    for (size_t i = 0; i < size_a; ++i, ptr_a+=type_size, ptr_b+=type_size) {
        assert_written_ok(
            snprintf(buff_a, STR_SIZE, "%s at index %zu", name_a, i), STR_SIZE
        );
        assert_written_ok(
            snprintf(buff_b, STR_SIZE, "%s at index %zu", name_b, i), STR_SIZE
        );
        tmp = assert_op(
            OP_E, 
            ptr_a, type_size, type_a, buff_a,
            ptr_b, type_size, type_b, buff_b,
            false
        );
        if (tmp == false) {
            success = false;
        }
    }
    if(success == false) {
        printf("---\n%s == %s FAILED\n", name_a, name_b);
        printf("├── 1st: %s: ", name_a);
        array_print(a, size_a, type_size, type_a, ",");
        printf("└── 2st: %s: ", name_b);
        array_print(b, size_b, type_size, type_b, ",");
        abort();   
    }
}

#ifndef TESTSUIT_H
#define TESTSUIT_H
#include <stdio.h>
#include <stdint.h>
#include "tools.h"

#define true 1
#define false 0

/**
 * @brief  Assert equality of a and b.
 * @note   Only works with variable defined in variable_t.
 *         Aborts, if assertion fails.
 * @param  a: First variable to test.
 * @param  b: Second variable to test.
 * @retval None.
 */
#define ASSERT_EQUAL(a, b) \
    assert_op(OP_E, \
              &a, sizeof(a), T2V_T(a), #a, \
              &b, sizeof(b), T2V_T(b), #b, \
              true)

/**
 * @brief  Assert operation success between a and b.
 * @note   Only works with variable defined in variable_t.
 *         Aborts, if assertion fails.
 * @param  op: Operation (op_t) to test.
 * @param  a: First variable to test.
 * @param  b: Second variable to test.
 * @retval None.
 */
#define ASSERT_OP(op, a, b) \
    assert_op(op, \
              &a, sizeof(a), T2V_T(a), #a, \
              &b, sizeof(b), T2V_T(b), #b, \
              true)

/**
 * @brief  Assert a is greater than b.
 * @note   Only works with variable defined in variable_t.
 *         Aborts, if assertion fails.
 * @param  a: First variable to test.
 * @param  b: Second variable to test.
 * @retval None.
 */
#define ASSERT_GREATER(a, b) \
    ASSERT_OP(OP_GT, a, b)

/**
 * @brief  Assert a is greater than or equal to b.
 * @note   Only works with variable defined in variable_t.
 *         Aborts, if assertion fails.
 * @param  a: First variable to test.
 * @param  b: Second variable to test.
 * @retval None.
 */
#define ASSERT_GREATER_OR_EQUAL(a, b) \
    ASSERT_OP(OP_GT | OP_E, a, b)

/**
 * @brief  Assert a is lesser than b.
 * @note   Only works with variable defined in variable_t.
 *         Aborts, if assertion fails.
 * @param  a: First variable to test.
 * @param  b: Second variable to test.
 * @retval None.
 */
#define ASSERT_LESSER(a, b) \
    ASSERT_OP(OP_LT, a, b)

/**
 * @brief  Assert a is greater than or equal to b.
 * @note   Only works with variable defined in variable_t.
 *         Aborts, if assertion fails.
 * @param  a: First variable to test.
 * @param  b: Second variable to test.
 * @retval None.
 */
#define ASSERT_LESSER_OR_EQUAL(a, b) \
    ASSERT_OP(OP_LT | OP_E, a, b)

/**
 * @brief  Assert array a is equal to array b.
 * @note   Only works with arrays of variables defined in variable_t.
 *         Aborts, if an assertion fails. 
 * @param  a: array a.
 * @param  size_a: Size of array a.
 * @param  b: array b.
 * @param  size_b: Size of array b.
 * @retval 
 */
#define ASSERT_COLLECTION_EQUAL(a, size_a, b, size_b) \
    assert_collection_equal(a, size_a, T2V_T(*a), #a, \
                            b, size_b, T2V_T(*b), #b, \
                            sizeof(*a))

typedef uint8_t bool;

/**
 * @brief  Operation type. Can be used with flags.
 * @note   For instance OP_GT | OP_E representes ">="
 */
typedef enum {
    OP_NONE = 0b0000,
    OP_E    = 0b0001,
    OP_GT   = 0b0010,
    OP_LT   = 0b0100,
} op_t;

/**
 * @brief  Assert operation success between two values.
 * @note   Only works with variables defined in variable_t.
 *         Aborts, if an assertion fails. 
 * @param  op: Operation to test.
 * @param  ptr_a: Pointer to value a.
 * @param  size_a: Size of value a.
 * @param  type_a: Type of value a.
 * @param  name_a: Name of value a.
 * @param  ptr_b: Pointer to value b.
 * @param  size_b: Size of value b.
 * @param  type_b: Type of value b.
 * @param  name_b: Name of value b.
 * @param  abort_on_fail: Whether to abort on assertion fail.
 * @retval Whether assertion succeded.
 */
bool assert_op(op_t op, 
               const void* ptr_a, const size_t size_a, 
               const variable_t type_a, const char* name_a,
               const void* ptr_b, const size_t size_b,
               const variable_t type_b, const char* name_b,
               const bool abort_on_fail);

/**
 * @brief  Assert two arrays are equal.
 * @note   Only works with arrays of variables defined in variable_t.
 *         Aborts, if an assertion fails. 
 * @param  a: Array a.
 * @param  size_a: Size of array a.
 * @param  type_a: Type of array a.
 * @param  name_a: Name of array a.
 * @param  b: Array b.
 * @param  size_b: Size of array b.
 * @param  type_b: Type of array b.
 * @param  name_b: Name of array b.
 * @param  type_size: Size of array item type.
 * @retval None
 */
void assert_collection_equal(void* a, const size_t size_a, 
                             const variable_t type_a, const char* name_a,
                             void* b, const size_t size_b,
                             const variable_t type_b, const char* name_b,
                             size_t type_size);

#endif

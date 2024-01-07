/*
 * @author polaris
 * @description cstl_stack.h created on 2023-12-10 
 */

#ifndef LIBTREASURE_CSTL_STACK_H
#define LIBTREASURE_CSTL_STACK_H

#include "cstl_list.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"{
#endif

typedef cstl_list_t cstl_stack_t;

cstl_stack_t *cstl_stack_create(cstl_dup_func dup, cstl_free_func free);

int32_t cstl_stack_push(cstl_stack_t *stack, cstl_data_t data);

cstl_data_t cstl_stack_pop(cstl_stack_t *stack);

cstl_data_t cstl_stack_peek(const cstl_stack_t *stack);

size_t cstl_stack_get_num(const cstl_stack_t *stack);

void cstl_stack_destroy(cstl_stack_t *stack);

inline cstl_stack_t *cstl_stack_create(cstl_dup_func dup, cstl_free_func free) { return cstl_list_create(dup, free); }

inline int32_t cstl_stack_push(cstl_stack_t *stack, cstl_data_t data) { return cstl_list_add_tail(stack, data); }

inline cstl_data_t cstl_stack_pop(cstl_stack_t *stack) { return cstl_list_pop_tail(stack); }

inline cstl_data_t cstl_stack_peek(const cstl_stack_t *stack) { return cstl_list_peek_tail(stack); }

inline size_t cstl_stack_get_num(const cstl_stack_t *stack) { return cstl_list_get_num(stack); }

inline void cstl_stack_destroy(cstl_stack_t *stack) { return cstl_list_destroy(stack); }

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_STACK_H */

/*
 * @author polaris
 * @description cstl_list.h created on 2023-12-02 
 */

#ifndef LIBTREASURE_CSTL_LIST_H
#define LIBTREASURE_CSTL_LIST_H

#include <stddef.h>
#include "cstl_defines.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"{
#endif

typedef struct cstl_list cstl_list_t;

cstl_list_t *cstl_list_create(cstl_dup_func dup, cstl_free_func free);

int32_t cstl_list_add_head(cstl_list_t *list, void *data);

int32_t cstl_list_add_tail(cstl_list_t *list, void *data);

void *cstl_list_pop_head(cstl_list_t *list);

void *cstl_list_pop_tail(cstl_list_t *list);

void *cstl_list_peek_head(const cstl_list_t *list);

void *cstl_list_peek_tail(const cstl_list_t *list);

size_t cstl_list_get_num(const cstl_list_t *list);

void cstl_list_destroy(cstl_list_t *list);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_LIST_H */

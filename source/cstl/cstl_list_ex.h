/*
 * @author polaris
 * @description cstl_list_ex.h created on 2024-01-01
 */

#ifndef LIBTREASURE_CSTL_LIST_EX_H
#define LIBTREASURE_CSTL_LIST_EX_H

#include "cstl_default_impl.h"
#include "cstl_list.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#define CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(type, name)                 \
    cstl_list_t *cstl_list_##name##_create(void);                       \
    int32_t cstl_list_##name##_add_head(cstl_list_t *list, type data);  \
    int32_t cstl_list_##name##_add_tail(cstl_list_t *list, type data);  \
    type cstl_list_##name##_pop_head(cstl_list_t *list);                \
    type cstl_list_##name##_pop_tail(cstl_list_t *list);                \
    type cstl_list_##name##_peek_head(const cstl_list_t *list);         \
    type cstl_list_##name##_peek_tail(const cstl_list_t *list);         \
    size_t cstl_list_##name##_get_num(const cstl_list_t *list);         \
    void cstl_list_##name##_destroy(cstl_list_t *list);

CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(uint8_t, u8)

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_LIST_EX_H */

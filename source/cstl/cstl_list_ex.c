#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-macro-parentheses"
/*
 * @author polaris
 * @description cstl_list_ex.c created on 2024-01-01 
 */

#include "cstl_list_ex.h"

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_CREATE(name) \
    cstl_list_t *cstl_list_##name##_create(void) { return cstl_list_create(cstl_not_dup, cstl_not_free); }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_ADD_HEAD(type, name)           \
    int32_t cstl_list_##name##_add_head(cstl_list_t *list, type data) { \
        return cstl_list_add_head(list, (void *)data);                  \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_ADD_TAIL(type, name)           \
    int32_t cstl_list_##name##_add_tail(cstl_list_t *list, type data) { \
        return cstl_list_add_tail(list, (void *)data);                  \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_POP_HEAD(type, name)   \
    type cstl_list_##name##_pop_head(cstl_list_t *list) {       \
        return (type)cstl_list_pop_head(list);                  \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_POP_TAIL(type, name)   \
    type cstl_list_##name##_pop_tail(cstl_list_t *list) {       \
        return (type)cstl_list_pop_tail(list);                  \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_PEEK_HEAD(type, name)      \
    type cstl_list_##name##_peek_head(const cstl_list_t *list) {    \
        return (type)cstl_list_peek_head(list);                     \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_PEEK_TAIL(type, name)      \
    type cstl_list_##name##_peek_tail(const cstl_list_t *list) {    \
        return (type)cstl_list_peek_tail(list);                     \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_GET_NUM(type, name)        \
    size_t cstl_list_##name##_get_num(const cstl_list_t *list) {    \
        return cstl_list_get_num(list);                             \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_DESTROY(type, name)    \
    void cstl_list_##name##_destroy(cstl_list_t *list) {        \
        cstl_list_destroy(list);                                \
    }


#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(type, name)       \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_CREATE(name)           \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_ADD_HEAD(type, name)   \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_ADD_TAIL(type, name)   \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_POP_HEAD(type, name)   \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_POP_TAIL(type, name)   \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_PEEK_HEAD(type, name)  \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_PEEK_TAIL(type, name)  \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_GET_NUM(type, name)    \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_DESTROY(type, name)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(uint8_t, u8)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(uint16_t, u16)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(uint32_t, u32)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(uint64_t, u64)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(int8_t, s8)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(int16_t, s16)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(int32_t, s32)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(int64_t, s64)

#pragma clang diagnostic pop
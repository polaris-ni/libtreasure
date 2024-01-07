/*
 * @author polaris
 * @description cstl_list_ex.c created on 2024-01-01 
 */

#include "cstl_list_ex.h"

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_ADD_HEAD(type, name)           \
    int32_t cstl_list_##name##_add_head(cstl_list_t *list, type data) { \
        cstl_data_t temp = { .name = data };                            \
        return cstl_list_add_head(list, temp);                          \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_ADD_TAIL(type, name)           \
    int32_t cstl_list_##name##_add_tail(cstl_list_t *list, type data) { \
        cstl_data_t temp = { .name = data };                            \
        return cstl_list_add_tail(list, temp);                          \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_POP_HEAD(type, name)           \
    type cstl_list_##name##_pop_head(cstl_list_t *list) {               \
        return cstl_list_pop_head(list).name;                           \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_POP_TAIL(type, name)           \
    type cstl_list_##name##_pop_tail(cstl_list_t *list) {               \
        return cstl_list_pop_tail(list).name;                           \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_PEEK_HEAD(type, name)          \
    type cstl_list_##name##_peek_head(const cstl_list_t *list) {        \
        return cstl_list_peek_head(list).name;                          \
    }

#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_PEEK_TAIL(type, name)          \
    type cstl_list_##name##_peek_tail(const cstl_list_t *list) {        \
        return cstl_list_peek_tail(list).name;                          \
    }


#define CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(type, name)                   \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_ADD_HEAD(type, name)               \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_ADD_TAIL(type, name)               \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_POP_HEAD(type, name)               \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_POP_TAIL(type, name)               \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_PEEK_HEAD(type, name)              \
    CSTL_LIST_IMPL_BASE_TYPE_EX_FUNC_PEEK_TAIL(type, name)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(uint8_t, u8)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(uint16_t, u16)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(uint32_t, u32)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(uint64_t, u64)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(int8_t, s8)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(int16_t, s16)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(int32_t, s32)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(int64_t, s64)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(float, f32)

CSTL_LIST_IMPL_BASE_TYPE_EX_FUNCS(double, f64)

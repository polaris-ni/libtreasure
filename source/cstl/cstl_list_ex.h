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

#define CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(type, name)                           \
    int32_t cstl_list_##name##_add_head(cstl_list_t *list, type data);            \
    int32_t cstl_list_##name##_add_tail(cstl_list_t *list, type data);            \
    int32_t cstl_list_##name##_insert(cstl_list_t *list, type data, size_t index);

CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(uint8_t, u8)
CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(uint16_t, u16)
CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(uint32_t, u32)
CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(uint64_t, u64)
CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(int8_t, s8)
CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(int16_t, s16)
CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(int32_t, s32)
CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(int64_t, s64)
CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(float, f32)
CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(double, f64)
CSTL_DECLARE_BASE_TYPE_LIST_EX_FUNC(void*, any)

#define CSTL_LIST_GET_NAME(data_type, suf) CSTL_GET_NAME(list, data_type, suf)

#define cstl_list_create_ex() cstl_list_create(cstl_not_dup, cstl_not_free)

#define cstl_list_pop_head_ex(list) cstl_list_pop_head(list)

#define cstl_list_pop_tail_ex(list) cstl_list_pop_tail(list)

#define cstl_list_peek_head_ex(list) cstl_list_peek_head(list)

#define cstl_list_peek_tail_ex(list) cstl_list_peek_tail(list)

#define cstl_list_remove_ex(list) cstl_list_get_num(list)

#define cstl_list_get_num_ex(list) cstl_list_get_num(list)

#define cstl_list_destroy_ex(list) cstl_list_destroy(list)

#define cstl_list_add_head_ex(list, data) _Generic((data),      \
    uint8_t : CSTL_LIST_GET_NAME(u8, add_head)(list, data),     \
    int8_t : CSTL_LIST_GET_NAME(s8, add_head)(list, data),      \
    uint16_t : CSTL_LIST_GET_NAME(u16, add_head)(list, data),   \
    int16_t : CSTL_LIST_GET_NAME(s16, add_head)(list, data),    \
    uint32_t : CSTL_LIST_GET_NAME(u32, add_head)(list, data),   \
    int32_t : CSTL_LIST_GET_NAME(s32, add_head)(list, data),    \
    uint64_t : CSTL_LIST_GET_NAME(u64, add_head)(list, data),   \
    int64_t : CSTL_LIST_GET_NAME(s64, add_head)(list, data),    \
    float: CSTL_LIST_GET_NAME(f32, add_head)(list, data),       \
    double: CSTL_LIST_GET_NAME(f64, add_head)(list, data),      \
    default: CSTL_LIST_GET_NAME(any, add_head)(list, data)      \
)

#define cstl_list_add_tail_ex(list, data) _Generic((data),      \
    uint8_t : CSTL_LIST_GET_NAME(u8, add_tail)(list, data),     \
    int8_t : CSTL_LIST_GET_NAME(s8, add_tail)(list, data),      \
    uint16_t : CSTL_LIST_GET_NAME(u16, add_tail)(list, data),   \
    int16_t : CSTL_LIST_GET_NAME(s16, add_tail)(list, data),    \
    uint32_t : CSTL_LIST_GET_NAME(u32, add_tail)(list, data),   \
    int32_t : CSTL_LIST_GET_NAME(s32, add_tail)(list, data),    \
    uint64_t : CSTL_LIST_GET_NAME(u64, add_tail)(list, data),   \
    int64_t : CSTL_LIST_GET_NAME(s64, add_tail)(list, data),    \
    float: CSTL_LIST_GET_NAME(f32, add_tail)(list, data),       \
    double: CSTL_LIST_GET_NAME(f64, add_tail)(list, data),      \
    default: CSTL_LIST_GET_NAME(any, add_tail)(list, data)      \
)

#define cstl_list_insert_ex(list, data, index) _Generic((data),     \
    uint8_t : CSTL_LIST_GET_NAME(u8, insert)(list, data, index),    \
    int8_t : CSTL_LIST_GET_NAME(s8, insert)(list, data, index),     \
    uint16_t : CSTL_LIST_GET_NAME(u16, insert)(list, data, index),  \
    int16_t : CSTL_LIST_GET_NAME(s16, insert)(list, data, index),   \
    uint32_t : CSTL_LIST_GET_NAME(u32, insert)(list, data, index),  \
    int32_t : CSTL_LIST_GET_NAME(s32, insert)(list, data, index),   \
    uint64_t : CSTL_LIST_GET_NAME(u64, insert)(list, data, index),  \
    int64_t : CSTL_LIST_GET_NAME(s64, insert)(list, data, index),   \
    float: CSTL_LIST_GET_NAME(f32, insert)(list, data, index),      \
    double: CSTL_LIST_GET_NAME(f64, insert)(list, data, index),     \
    default: CSTL_LIST_GET_NAME(any, insert)(list, data, index)     \
)

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_LIST_EX_H */

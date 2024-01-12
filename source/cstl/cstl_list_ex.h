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
    int32_t cstl_list_##name##_add_head(cstl_list_t *list, type data);  \
    int32_t cstl_list_##name##_add_tail(cstl_list_t *list, type data);  \
    type cstl_list_##name##_pop_head(cstl_list_t *list);                \
    type cstl_list_##name##_pop_tail(cstl_list_t *list);                \
    type cstl_list_##name##_peek_head(const cstl_list_t *list);         \
    type cstl_list_##name##_peek_tail(const cstl_list_t *list);

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

#define CSTL_LIST_GET_NAME(data_type, suf) CSTL_GET_NAME(list, data_type, suf)

#define cstl_list_create_ex() cstl_list_create(cstl_not_dup, cstl_not_free)

#define cstl_list_get_num_ex() cstl_list_get_num()

#define cstl_list_destroy_ex() cstl_list_destroy()

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
    default: cstl_list_add_head(list, (void *)data)             \
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
    default: cstl_list_add_tail(list, (void *)data)             \
)

#define cstl_list_pop_head_ex(list, data) _Generic((data),  \
    uint8_t : CSTL_LIST_GET_NAME(u8, pop_head)(list),       \
    int8_t : CSTL_LIST_GET_NAME(s8, pop_head)(list),        \
    uint16_t : CSTL_LIST_GET_NAME(u16, pop_head)(list),     \
    int16_t : CSTL_LIST_GET_NAME(s16, pop_head)(list),      \
    uint32_t : CSTL_LIST_GET_NAME(u32, pop_head)(list),     \
    int32_t : CSTL_LIST_GET_NAME(s32, pop_head)(list),      \
    uint64_t : CSTL_LIST_GET_NAME(u64, pop_head)(list),     \
    int64_t : CSTL_LIST_GET_NAME(s64, pop_head)(list),      \
    float: CSTL_LIST_GET_NAME(f32, pop_head)(list, data),   \
    double: CSTL_LIST_GET_NAME(f64, pop_head)(list, data),  \
    default: cstl_list_pop_head(list)                       \
)

#define cstl_list_pop_tail_ex(list, data) _Generic((data),  \
    uint8_t : CSTL_LIST_GET_NAME(u8, pop_tail)(list),       \
    int8_t : CSTL_LIST_GET_NAME(s8, pop_tail)(list),        \
    uint16_t : CSTL_LIST_GET_NAME(u16, pop_tail)(list),     \
    int16_t : CSTL_LIST_GET_NAME(s16, pop_tail)(list),      \
    uint32_t : CSTL_LIST_GET_NAME(u32, pop_tail)(list),     \
    int32_t : CSTL_LIST_GET_NAME(s32, pop_tail)(list),      \
    uint64_t : CSTL_LIST_GET_NAME(u64, pop_tail)(list),     \
    int64_t : CSTL_LIST_GET_NAME(s64, pop_tail)(list),      \
    float: CSTL_LIST_GET_NAME(f32, pop_tail)(list, data),   \
    double: CSTL_LIST_GET_NAME(f64, pop_tail)(list, data),  \
    default: cstl_list_pop_tail(list)                       \
)

#define cstl_list_peek_head_ex(list, data) _Generic((data), \
    uint8_t : CSTL_LIST_GET_NAME(u8, peek_head)(list),      \
    int8_t : CSTL_LIST_GET_NAME(s8, peek_head)(list,        \
    uint16_t : CSTL_LIST_GET_NAME(u16, peek_head)(list),    \
    int16_t : CSTL_LIST_GET_NAME(s16, peek_head)(list),     \
    uint32_t : CSTL_LIST_GET_NAME(u32, peek_head)(list),    \
    int32_t : CSTL_LIST_GET_NAME(s32, peek_head)(list),     \
    uint64_t : CSTL_LIST_GET_NAME(u64, peek_head)(list),    \
    int64_t : CSTL_LIST_GET_NAME(s64, peek_head)(list),     \
    float: CSTL_LIST_GET_NAME(f32, peek_head)(list, data),  \
    double: CSTL_LIST_GET_NAME(f64, peek_head)(list, data), \
    default: cstl_list_peek_head(list)                      \
)

#define cstl_list_peek_tail_ex(list, data) _Generic((data), \
    uint8_t : CSTL_LIST_GET_NAME(u8, peek_tail)(list),      \
    int8_t : CSTL_LIST_GET_NAME(s8, peek_tail)(list),       \
    uint16_t : CSTL_LIST_GET_NAME(u16, peek_tail)(list),    \
    int16_t : CSTL_LIST_GET_NAME(s16, peek_tail)(list),     \
    uint32_t : CSTL_LIST_GET_NAME(u32, peek_tail)(list),    \
    int32_t : CSTL_LIST_GET_NAME(s32, peek_tail)(list),     \
    uint64_t : CSTL_LIST_GET_NAME(u64, peek_tail)(list),    \
    int64_t : CSTL_LIST_GET_NAME(s64, peek_tail)(list,      \
    float: CSTL_LIST_GET_NAME(f32, peek_tail)(list, data),  \
    double: CSTL_LIST_GET_NAME(f64, peek_tail)(list, data), \
    default: cstl_list_peek_tail(list)                      \
)

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_LIST_EX_H */

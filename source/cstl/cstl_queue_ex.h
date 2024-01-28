/*
 * @author polaris
 * @description cstl_queue_ex.h created on 2024-01-12
 */

#ifndef LIBTREASURE_CSTL_QUEUE_EX_H
#define LIBTREASURE_CSTL_QUEUE_EX_H

#include "cstl_queue.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#define CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(type, name)                       \
  int32_t cstl_queue_##name##_enqueue(cstl_queue_t *queue, type data);         \
  type cstl_queue_##name##_dequeue(cstl_queue_t *queue);                       \
  type cstl_queue_##name##_peek(cstl_queue_t *queue);

CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(uint8_t, u8)
CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(uint16_t, u16)
CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(uint32_t, u32)
CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(uint64_t, u64)
CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(int8_t, s8)
CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(int16_t, s16)
CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(int32_t, s32)
CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(int64_t, s64)
CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(float, f32)
CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(double, f64)
CSTL_DECLARE_BASE_TYPE_QUEUE_EX_FUNC(void*, any)

#define cstl_queue_create_ex() cstl_queue_create(cstl_not_dup, cstl_not_free)

#define cstl_queue_destroy_ex(queue) cstl_queue_destroy(queue)

#define CSTL_QUEUE_GET_NAME(data_type, suf) CSTL_GET_NAME(queue, data_type, suf)

#define cstl_queue_enqueue_ex(queue, data) _Generic((data),     \
    uint8_t : CSTL_QUEUE_GET_NAME(u8, enqueue)(queue, data),    \
    int8_t : CSTL_QUEUE_GET_NAME(s8, enqueue)(queue, data),     \
    uint16_t : CSTL_QUEUE_GET_NAME(u16, enqueue)(queue, data),  \
    int16_t : CSTL_QUEUE_GET_NAME(s16, enqueue)(queue, data),   \
    uint32_t : CSTL_QUEUE_GET_NAME(u32, enqueue)(queue, data),  \
    int32_t : CSTL_QUEUE_GET_NAME(s32, enqueue)(queue, data),   \
    uint64_t : CSTL_QUEUE_GET_NAME(u64, enqueue)(queue, data),  \
    int64_t : CSTL_QUEUE_GET_NAME(s64, enqueue)(queue, data),   \
    float: CSTL_QUEUE_GET_NAME(f32, enqueue)(queue, data),      \
    double: CSTL_QUEUE_GET_NAME(f64, enqueue)(queue, data),     \
    default: CSTL_QUEUE_GET_NAME(any, enqueue)(queue, data)     \
)

#define cstl_queue_dequeue_ex(queue, data) _Generic((data),     \
    uint8_t : CSTL_QUEUE_GET_NAME(u8, dequeue)(queue),    \
    int8_t : CSTL_QUEUE_GET_NAME(s8, dequeue)(queue),     \
    uint16_t : CSTL_QUEUE_GET_NAME(u16, dequeue)(queue),  \
    int16_t : CSTL_QUEUE_GET_NAME(s16, dequeue)(queue),   \
    uint32_t : CSTL_QUEUE_GET_NAME(u32, dequeue)(queue),  \
    int32_t : CSTL_QUEUE_GET_NAME(s32, dequeue)(queue),   \
    uint64_t : CSTL_QUEUE_GET_NAME(u64, dequeue)(queue),  \
    int64_t : CSTL_QUEUE_GET_NAME(s64, dequeue)(queue),   \
    float: CSTL_QUEUE_GET_NAME(f32, dequeue)(queue),      \
    double: CSTL_QUEUE_GET_NAME(f64, dequeue)(queue),     \
    default: CSTL_QUEUE_GET_NAME(any, dequeue)(queue)     \
)

#define cstl_queue_peek_ex(queue) _Generic((data),     \
    uint8_t : CSTL_QUEUE_GET_NAME(u8, peek)(queue),    \
    int8_t : CSTL_QUEUE_GET_NAME(s8, peek)(queue),     \
    uint16_t : CSTL_QUEUE_GET_NAME(u16, peek)(queue),  \
    int16_t : CSTL_QUEUE_GET_NAME(s16, peek)(queue),   \
    uint32_t : CSTL_QUEUE_GET_NAME(u32, peek)(queue),  \
    int32_t : CSTL_QUEUE_GET_NAME(s32, peek)(queue),   \
    uint64_t : CSTL_QUEUE_GET_NAME(u64, peek)(queue),  \
    int64_t : CSTL_QUEUE_GET_NAME(s64, peek)(queue),   \
    float: CSTL_QUEUE_GET_NAME(f32, peek)(queue),      \
    double: CSTL_QUEUE_GET_NAME(f64, peek)(queue),     \
    default: CSTL_QUEUE_GET_NAME(any, peek)(queue)     \
)


#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_QUEUE_EX_H */

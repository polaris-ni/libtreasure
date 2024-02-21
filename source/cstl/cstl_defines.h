/*
 * @author polaris
 * @description cstl_defines.h created on 2023-12-02
 */

#ifndef LIBTREASURE_CSTL_DEFINES_H
#define LIBTREASURE_CSTL_DEFINES_H

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include "treasure_log.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#ifndef EOK
#define EOK 0
#endif

//enum {
//    CSTL_SUCCESS,
//    CSTL_ERROR,
//    CSTL_BAD_PARAMS,
//    CSTL_ITEM_NOT_FOUND,
//    CSTL_MALLOC_ERROR
//};

typedef union cstl_data {
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    int8_t s8;
    int16_t s16;
    int32_t s32;
    int64_t s64;
    float f32;
    double f64;
    void *any;
} cstl_data_t;

typedef bool (*cstl_dup_func)(const cstl_data_t *src, cstl_data_t *dest);

typedef void (*cstl_free_func)(cstl_data_t *data);

typedef struct cstl_dup_free {
    cstl_dup_func dup;
    cstl_free_func free;
} cstl_func_pair;

static const cstl_data_t CSTL_INVALID_DATA = {0};

typedef struct cstl_node cstl_node_t;
struct cstl_node {
    cstl_data_t data;
    cstl_node_t *prev;
    cstl_node_t *next;
};

#define CSTL_MODULE_NAME "cstl"

#define CSTL_LOGD(fmt, args...) TREASURE_LOGD(CSTL_MODULE_NAME, fmt, ##args)
#define CSTL_LOGI(fmt, args...) TREASURE_LOGI(CSTL_MODULE_NAME, fmt, ##args)
#define CSTL_LOGW(fmt, args...) TREASURE_LOGW(CSTL_MODULE_NAME, fmt, ##args)
#define CSTL_LOGE(fmt, args...) TREASURE_LOGE(CSTL_MODULE_NAME, fmt, ##args)
#define CSTL_LOGF(fmt, args...) TREASURE_LOGF(CSTL_MODULE_NAME, fmt, ##args)

#define CSTL_RET_IF_NULL_OR_EMPTY(ptr, ret) \
    if (ptr == NULL) {                      \
        errno = ENOENT;                     \
        CSTL_LOGE(#ptr " is null.");        \
        return ret;                         \
    }                                       \
    if (ptr->num == 0) {                    \
        errno = ENOENT;                     \
        CSTL_LOGW(#ptr " is empty.");       \
        return ret;                         \
    }

#define CSTL_RET_IF_NULL(ptr, ret)      \
    if (ptr == NULL) {                  \
        errno = ENOENT;                 \
        CSTL_LOGE(#ptr " is null.");    \
        return ret;                     \
    }

#define CSTL_RET_NULL_IF_NULL(ptr) CSTL_RET_IF_NULL(ptr, NULL)

#define CSTL_UNUSED __attribute__((unused))

#define CSTL_GET_NAME(cstl_type, data_type, suf) cstl_##cstl_type##_##data_type##_##suf

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_DEFINES_H */

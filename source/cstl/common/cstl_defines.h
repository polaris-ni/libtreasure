/*
 * @author polaris
 * @description cstl_defines.h created on 2023-12-02
 */

#ifndef LIBTREASURE_CSTL_DEFINES_H
#define LIBTREASURE_CSTL_DEFINES_H

#include <stdint.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"{
#endif

enum {
    CSTL_SUCCESS,
    CSTL_ERROR
};

typedef void *(*cstl_dup_func)(void *);

typedef void (*cstl_free_func)(void *);

typedef struct cstl_node cstl_node_t;
struct cstl_node {
    void *data;
    cstl_node_t *prev;
    cstl_node_t *next;
};

#define CSTL_RET_IF_NULL_OR_EMPTY(ptr, ret) \
    if (ptr == NULL || ptr->num == 0) {     \
        return ret;                         \
    }

#define CSTL_RET_IF_NULL(ptr, ret)  \
    if (ptr == NULL) {              \
        return ret;                 \
    }

#define CSTL_RET_NULL_IF_NULL(ptr) CSTL_RET_IF_NULL(ptr, NULL)

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_DEFINES_H */

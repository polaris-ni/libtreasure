/*
 * @author polaris
 * @description cstl_queue.h created on 2023-12-02
 */

#ifndef LIBTREASURE_CSTL_QUEUE_H
#define LIBTREASURE_CSTL_QUEUE_H

#include "cstl_defines.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"{
#endif

typedef struct cstl_queue cstl_queue_t;

cstl_queue_t *cstl_queue_create(cstl_dup_func dup, cstl_free_func free);

int32_t cstl_queue_enqueue(cstl_queue_t *queue, void *data);

void *cstl_queue_dequeue(cstl_queue_t *queue);

void *cstl_queue_peek(cstl_queue_t *queue);

void cstl_queue_destroy(cstl_queue_t *queue);

size_t cstl_queue_get_num(cstl_queue_t *queue);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* LIBTREASURE_CSTL_QUEUE_H */

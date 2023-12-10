/*
 * @author polaris
 * @description cstl_queue.h created on 2023-12-02
 */

#ifndef LIBTREASURE_CSTL_QUEUE_H
#define LIBTREASURE_CSTL_QUEUE_H

#include "cstl_list.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"{
#endif

typedef cstl_list_t cstl_queue_t;

cstl_queue_t *cstl_queue_create(cstl_dup_func dup, cstl_free_func free);

int32_t cstl_queue_enqueue(cstl_queue_t *queue, void *data);

void *cstl_queue_dequeue(cstl_queue_t *queue);

void *cstl_queue_peek(const cstl_queue_t *queue);

size_t cstl_queue_get_num(const cstl_queue_t *queue);

void cstl_queue_destroy(cstl_queue_t *queue);

inline cstl_queue_t *cstl_queue_create(cstl_dup_func dup, cstl_free_func free) { return cstl_list_create(dup, free); }

inline int32_t cstl_queue_enqueue(cstl_queue_t *queue, void *data) { return cstl_list_add_tail(queue, data); }

inline void *cstl_queue_dequeue(cstl_queue_t *queue) { return cstl_list_pop_head(queue); }

inline void *cstl_queue_peek(const cstl_queue_t *queue) { return cstl_list_peek_head(queue); }

inline size_t cstl_queue_get_num(const cstl_queue_t *queue) { return cstl_list_get_num(queue); }

inline void cstl_queue_destroy(cstl_queue_t *queue) { return cstl_list_destroy(queue); }

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* LIBTREASURE_CSTL_QUEUE_H */

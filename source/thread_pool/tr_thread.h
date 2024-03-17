/**
 * @author polaris
 * @description tr_thread.h created on 2024-03-17
 */

#ifndef LIBTREASURE_TR_THREAD_H
#define LIBTREASURE_TR_THREAD_H

#include <stddef.h>
#include "tr_thread_pool_common.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef struct tr_thread thread_t;

typedef enum {
    STATE_INVALID,
    STATE_CREATED,
    STATE_IDLE,
    STATE_WORKING
} thread_state;

/**
 * create a thread
 * @param pool the pool that thread belong to
 * @return pointer to the thread
 */
thread_t *thread_create(thread_pool_t *pool);

/**
 * destroyed thread
 * @param thread to be destroyed [nullable]
 */
void thread_destroy(thread_t *thread);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* LIBTREASURE_TR_THREAD_H */

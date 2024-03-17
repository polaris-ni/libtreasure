/**
 * @author polaris
 * @description tr_thread_pool.h created on 2024-03-09
 */

#ifndef LIBTREASURE_TR_THREAD_POOL_H
#define LIBTREASURE_TR_THREAD_POOL_H

#include <stdint.h>
#include "tr_thread_pool_common.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/**
* create a thread pool
* @param core_thread_num the num of core thread, it should be 0 or bigger than 0
* @param max_thread_num the max num of threads in thread pool, it should be bigger than 0 or #TR_AUTO_THREADS
* @return pointer to #thread_pool_t, null if failed, errors will be set to errno
*/
thread_pool_t *thread_pool_create(uint32_t core_thread_num, int32_t max_thread_num);

/**
 * wait until thread pool is destroyed
 * @param pool pointer to #thread_pool_t
 */
void thread_pool_wait(thread_pool_t *pool);

/**
 * destroy the thread pool
 * @param pool the pool to be destroy [nullable]
 */
void thread_pool_destroy(thread_pool_t *pool);

/**
 * generate a new thread id
 * @param pool pool to generate thread id
 * @return a new thread_uid_t, #INVALID_THREAD_ID(0) will be returned if pool is NULL or thread id exceeds max
 */
thread_uid_t thread_pool_gen_thread_id(thread_pool_t *pool);

/**
 * add a task to thread pool
 * @param pool pointer to a created thread_pool_t
 * @param id return the id of task if success, ignore if id is NULL
 * @param worker work function
 * @param args params for #task_worker
 * @return errno[TBD]
 */
int32_t thread_pool_add_task(thread_pool_t *pool, task_id_t *id, task_worker *worker, void *args);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* LIBTREASURE_TR_THREAD_POOL_H */

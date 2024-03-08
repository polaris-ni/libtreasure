/**
 * @author polaris
 * @description tr_thread_pool.h created on 2024-03-09
 */

#ifndef LIBTREASURE_TR_THREAD_POOL_H
#define LIBTREASURE_TR_THREAD_POOL_H

#include <stdint.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef struct thread_pool thread_pool_t;

/**
* create a thread pool
* @param core_thread_num the num of core thread [non-negative]
* @param max_thread_num the max num of threads in thread pool [positive]
* @return pointer to #thread_pool_t, null if failed
*/
thread_pool_t *thread_pool_create(int32_t core_thread_num, int32_t max_thread_num);

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
 * add a task to thread pool
 * @param pool pointer to a created thread_pool_t
 * @param attr attribute of the task, it will be copied, and you can free it after #thread_pool_add_task
 * @param func work func, posix style
 * @param args params for #task_worker
 * @return #result_code
 */
int32_t thread_pool_add_task(thread_pool_t *pool, const task_attr_t *attr, work_func_posix *func, void *args);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* LIBTREASURE_TR_THREAD_POOL_H */

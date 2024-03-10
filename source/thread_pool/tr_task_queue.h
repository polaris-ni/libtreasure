/**
 * @author polaris
 * @description tr_task.h created on 2024-03-09
 */

#ifndef LIBTREASURE_TR_TASK_QUEUE_H
#define LIBTREASURE_TR_TASK_QUEUE_H

#include <stddef.h>
#include <stdint.h>
#include "tr_thread_pool_common.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef struct tr_task task_t;

typedef struct task_queue task_queue_t;

/**
 * create a task queue
 * @return pointer to #task_queue_t, NULL id failed, error will be set to #errno
 *         [ENOMEM] malloc failed
 */
task_queue_t *task_queue_create(void);

/**
 * add task to a queue
 * @param queue queue to be add task
 * @param cancel_type #task_cancel_type
 * @param worker it will be called with #args when task is executed
 * @param free it will only be called to free the #args when the task is cancelled.
 * @param args input parameter, nullable
 * @return [EOK] add task success
 *         [EINVAL] queue or worker or free is NULL
 *         [ENOMEM] malloc task/task_node failed
 */
int32_t task_queue_add_task(task_queue_t *queue, task_cancel_type cancel_type,
                            task_worker worker, task_free free, void *args);

/**
 * get out the earliest added task from the queue
 * @param queue #task_queue_t
 * @return the earliest added task, NULL id failed, error will be set to #errno
 *         [EINVAL] queue is NULL
 *         [ENOENT] queue is empty
 */
task_t *task_queue_pop_task(task_queue_t *queue);

/**
 * remove the task that id is equals to #id
 * @param queue queue to be remove task
 * @param id id of task that while be removed
 * @return [EOK] remove task success
 *         [EINVAL] queue is NULL or id is #INVALID_TASK_ID
 *         [ENOENT] not target task found
 */
int32_t task_queue_remove_task(task_queue_t *queue, task_id_t id);

/**
 * task queue enqueue
 * @param queue #task_queue_t
 * @param task the task to be enqueued
 * @return [EOK] enqueue success
 *         [EINVAL] queue or task is NULL
 *         [ENOMEM] malloc task node success
 */
int32_t task_queue_enqueue(task_queue_t *queue, task_t *task);

/**
 * task queue dequeue
 * @param queue #task_queue_t
 * @return the task dequeued from #queue, NULL id failed, error will be set to #errno
 *         [EINVAL] queue is NULL
 *         [ENOENT] queue is empty
 */
task_t *task_queue_dequeue(task_queue_t *queue);

/**
 * get the num of tasks in #queue
 * @param queue #task_queue_t
 * @return the num of tasks in #queue, if queue is NULL, errno will set to EINVAL and 0 will be returned
 */
size_t task_queue_get_num(const task_queue_t *queue);

/**
 * cancel and remove all tasks in #queue, id generator will not be reset
 * @param queue queue to be clear
 */
void task_queue_clear_task(task_queue_t *queue);

/**
 * destroy the queue, all tasks will be cancelled and removed first
 * @param queue queue to be destroyed
 */
void task_queue_destroy(task_queue_t *queue);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* LIBTREASURE_TR_TASK_QUEUE_H */

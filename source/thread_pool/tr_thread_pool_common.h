/**
 * @author polaris
 * @description tr_thread_pool_log.h created on 2024-03-09
 */

#ifndef LIBTREASURE_TR_THREAD_POOL_COMMON_H
#define LIBTREASURE_TR_THREAD_POOL_COMMON_H

#include "treasure_log.h"
#include "treasure_defines.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/**
* @param TASK_CANCEL_DISABLE task can not be cancelled
* @param TASK_CANCEL_LAZY task will be cancelled at the appropriate time
* @param TASK_CANCEL_PROMPT task will be cancelled intermediately
*/
typedef enum tr_task_cancel_type {
    TASK_CANCEL_DISABLE,
    TASK_CANCEL_LAZY,
    TASK_CANCEL_PROMPT
} task_cancel_type;

/**
 * work function, which will be called when task is executed
 */
typedef void *(*task_worker)(void *);

/**
 * free function will only be called to free the #args when the task is cancelled
 */
typedef void (*task_free)(void *args);

/**
 * identifier of task, unique in one task queue, maybe the same as a task in another queue
 */
typedef size_t task_id_t;

/**
 * identifier of thread, unique in one thread pool, maybe the same as a thread in another thread pool
 */
typedef size_t thread_uid_t;

typedef struct thread_pool thread_pool_t;

/**
 * thread pool won't limit the num of threads
 * if there is no free thread, pool will always create a new thread regardless of current active threads num
 */
#define TR_AUTO_THREADS (-1)

#define INVALID_TASK_ID 0u

#define INVALID_THREAD_ID 0u

#define TR_TP_MODULE_NAME "tr_thread_pool"

#define TR_TP_LOGD(fmt, args...) TREASURE_LOGD(TR_TP_MODULE_NAME, fmt, ##args)
#define TR_TP_LOGI(fmt, args...) TREASURE_LOGI(TR_TP_MODULE_NAME, fmt, ##args)
#define TR_TP_LOGW(fmt, args...) TREASURE_LOGW(TR_TP_MODULE_NAME, fmt, ##args)
#define TR_TP_LOGE(fmt, args...) TREASURE_LOGE(TR_TP_MODULE_NAME, fmt, ##args)
#define TR_TP_LOGF(fmt, args...) TREASURE_LOGF(TR_TP_MODULE_NAME, fmt, ##args)

#define TR_TP_RET_SET_IF(cond, err, msg, ret)   \
    if (cond) {                                 \
        errno = err;                            \
        TR_TP_LOGE(msg);                        \
        return ret;                             \
    }

#define TR_TP_RET_IF_NULL(ptr, ret)     \
    if (ptr == NULL) {                  \
        TR_TP_LOGE(#ptr " is NULL.");   \
        return ret;                     \
    }

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* LIBTREASURE_TR_THREAD_POOL_COMMON_H */

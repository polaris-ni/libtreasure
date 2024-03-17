/**
 * @author polaris
 * @description tr_thread.c created on 2024-03-17
 */

#include "tr_thread.h"
#include <errno.h>
#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
#include "tr_task_queue.h"
#include "tr_thread_pool.h"

struct tr_thread {
    thread_uid_t id;
    thread_state state;
    pthread_t pthread;
    task_t *task;
    thread_pool_t *pool;
    sem_t sem;
    pthread_mutex_t lock;
};

static int32_t thread_init(thread_pool_t *pool, thread_t *new_thread) {
    new_thread->id = thread_pool_gen_thread_id(pool);
    TR_TP_RET_SET_IF((new_thread->id == INVALID_THREAD_ID), errno, "generate id failed.", errno)
    new_thread->state = STATE_CREATED;
    new_thread->task = NULL;
    new_thread->pool = pool;
    if (sem_init(&new_thread->sem, 0, 0) != 0) {
        TR_TP_LOGE("init thread sem failed, err = %d.", errno);
        return errno;
    }
    if (pthread_mutex_init(&new_thread->lock, NULL) != 0) {
        (void) sem_destroy(&new_thread->sem);
        TR_TP_LOGE("init thread lock failed, err = %d.", errno);
        return errno;
    }
    TR_TP_LOGI("thread %zu init success.", new_thread->id);
    return EOK;
}

thread_t *thread_create(thread_pool_t *pool) {
    TR_TP_RET_IF_NULL(pool, NULL)
    thread_t *new_thread = (thread_t *) malloc(sizeof(thread_t));
    TR_TP_RET_IF_NULL(new_thread, NULL)
    if (thread_init(pool, new_thread) != EOK) {
        thread_destroy(new_thread);
        return NULL;
    }
    TR_TP_LOGI("create thread %llu success.", new_thread->id);
    return new_thread;
}

void thread_destroy(thread_t *thread) {
    if (thread == NULL) {
        TR_TP_LOGW("thread is null, maybe has been free.");
        return;
    }
    /* cancel thread */
    (void) sem_destroy(&thread->sem);
    (void) pthread_mutex_destroy(&thread->lock);
    free(thread);
}

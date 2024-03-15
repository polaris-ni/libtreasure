/**
 * @author polaris
 * @description tr_thread_pool.c created on 24-3-8
 */

#include "tr_thread_pool.h"
#include <stdbool.h>
#include <semaphore.h>
#include <malloc.h>
#include <memory.h>
#include <errno.h>
#include <pthread.h>
#include "tr_task_queue.h"
#include "treasure_defines.h"

typedef size_t thread_uid_t;

typedef enum {
    STATE_INVALID,
    STATE_IDLE,
    STATE_WORKING
} thread_state;

typedef struct tr_thread {
    thread_uid_t id;
    thread_state state;
    pthread_t pthread;
    task_t *task;
    thread_pool_t *pool;
    sem_t sem;
    pthread_mutex_t lock;
} thread_t;

typedef struct thread_node thread_node_t;
struct thread_node {
    thread_t *thread;
    struct thread_node *next;
};

struct thread_pool {
    bool is_flex;
    uint32_t core_num;
    uint32_t flex_num;
    uint32_t max_num;
    pthread_mutex_t lock;
    sem_t task_num;
    sem_t idle_thread_num;
    thread_uid_t id;
    task_queue_t *queue;
    thread_t *core_threads;
    thread_node_t flex_threads;
    pthread_t daemon_thread;
};

static int32_t thread_pool_init_attr(thread_pool_t *pool, uint32_t core_thread_num, int32_t max_thread_num) {
    pool->is_flex = (max_thread_num == TR_AUTO_THREADS);
    pool->core_num = core_thread_num;
    pool->flex_num = pool->is_flex ? 0 : (max_thread_num - core_thread_num);
    pool->max_num = max_thread_num;
    int32_t ret = pthread_mutex_init(&pool->lock, NULL);
    if (ret != 0) {
        TR_TP_LOGE("pthread_mutex_init failed, ret = %d.", ret);
        return ret;
    }
    ret = sem_init(&pool->task_num, 0, 0);
    if (ret != 0) {
        (void) pthread_mutex_destroy(&pool->lock);
        TR_TP_LOGE("sem_init task num failed, ret = %d.", ret);
        return ret;
    }
    ret = sem_init(&pool->idle_thread_num, 0, max_thread_num == TR_AUTO_THREADS ? core_thread_num : max_thread_num);
    if (ret != 0) {
        (void) pthread_mutex_destroy(&pool->lock);
        (void) sem_destroy(&pool->idle_thread_num);
        TR_TP_LOGE("sem_init idle threads num failed, ret = %d.", ret);
        return ret;
    }
    pool->id = 0;
    TR_TP_LOGI("thread pool attr init success.");
    return EOK;
}

static int32_t thread_pool_init_daemon_thread(thread_pool_t *pool) {
    /* TODO: 2024-3-10 polaris thread_pool_init_daemon_thread */
    return EOK;
}

static int32_t thread_pool_init_threads(thread_pool_t *pool, uint32_t core_thread_num, int32_t max_thread_num) {
    /* TODO: 2024-3-10 polaris thread_pool_init_threads */
    return EOK;
}

static void thread_pool_clear(thread_pool_t *pool) {
    /* 1. destroy flex threads */
    thread_node_t *node = pool->flex_threads.next;
    thread_node_t *last = &pool->flex_threads;
    while (node != NULL) {
        last = node;
        node = node->next;
        /* TODO: 2024-3-10 polaris close last.thread */
        last->thread = NULL;
        free(last);
    }
    /* 2. destroy core threads */
    pool->flex_threads.next = NULL;
    if (pool->core_threads != NULL) {
        for (uint32_t i = 0; i < pool->core_num; ++i) {
            /* TODO: 2024-3-10 polaris close all core threads */
        }
        free(pool->core_threads);
        pool->core_threads = NULL;
    }
    /* 3. destroy task queue */
    task_queue_destroy(pool->queue);
    /* 4. reset attrs and destroy sem & lock */
    pool->queue = NULL;
    pool->is_flex = false;
    pool->core_num = 0;
    pool->flex_num = 0;
    pool->max_num = 0;
    pool->id = 0;
    (void) pthread_mutex_destroy(&pool->lock);
    (void) sem_destroy(&pool->task_num);
    (void) sem_destroy(&pool->idle_thread_num);
}

void thread_pool_destroy(thread_pool_t *pool) {
    TR_TP_RET_IF_NULL(pool,)
    thread_pool_clear(pool);
}

thread_pool_t *thread_pool_create(uint32_t core_thread_num, int32_t max_thread_num) {
    TR_TP_RET_SET_IF(((max_thread_num != TR_AUTO_THREADS) && (core_thread_num > max_thread_num)), EINVAL,
                     "core threads num is bigger than max threads num, and not flexible thread pool.", NULL)
    thread_pool_t *temp = (thread_pool_t *) malloc(sizeof(thread_pool_t));
    if (temp == NULL) {
        errno = ENOMEM;
        TR_TP_LOGE("malloc thread pool failed.");
        return NULL;
    }
    (void) memset(temp, 0, sizeof(thread_pool_t));
    int32_t ret = EOK;
    do {
        temp->queue = task_queue_create();
        if (temp->queue == NULL) {
            ret = errno;
            TR_TP_LOGE("create task queue failed, errno = %d.", errno);
            break;
        }
        TR_TP_LOGI("init task queue success.");
        ret = thread_pool_init_attr(temp, core_thread_num, max_thread_num);
        if (ret != EOK) {
            break;
        }
        ret = thread_pool_init_daemon_thread(temp);
        if (ret != EOK) {
            break;
        }
        ret = thread_pool_init_threads(temp, core_thread_num, max_thread_num);
        if (ret != EOK) {
            break;
        }
        TR_TP_LOGI("init thread pool success.");
        return temp;
    } while (0);

    if (ret != EOK) {
        thread_pool_destroy(temp);
        temp = NULL;
    }
    return NULL;
}

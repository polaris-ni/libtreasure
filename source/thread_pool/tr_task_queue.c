/**
 * @author polaris
 * @description tr_task.c created on 2024-03-09
 */

#include "tr_task_queue.h"
#include <errno.h>
#include <stdlib.h>
#include "treasure_defines.h"

/**
 * @param type #task_type
 * @param flags #task_cancel_type
 * @see task_type
 * @see task_cancel_type
 */
typedef struct task_attr {
    task_cancel_type cancel_type;
    task_id_t id;
} task_attr_t;

struct tr_task {
    void *args;
    task_worker worker;
    task_free free;
    task_attr_t attr;
};

/**
 * @param task #task_t
 * @param pre previous #task_node_t
 * @note node_1 [tread as <head> ] -> node-2 -> ... -> node_n [tread as <tail>] -> NULL
 */
typedef struct task_node {
    task_t *task;
    struct task_node *next;
} task_node_t;

/**
 * @param count current queue member num, empty if head = tail = 0
 * @param front head pointer
 * @param read tail pointer
 * @param free task free func
 */
struct task_queue {
    size_t count;
    task_id_t id;
    task_node_t *head;
    task_node_t *tail;
};

static task_t *task_create(task_queue_t *queue, task_cancel_type type, task_worker func, task_free free, void *args) {
    task_t *task = (task_t *) malloc(sizeof(task_t));
    if (task == NULL) {
        errno = ENOMEM;
        TR_TP_LOGE("malloc task_t failed.");
        return NULL;
    }

    queue->id++;
    task->args = args;
    task->worker = func;
    task->free = free;
    task->attr.id = queue->id;
    task->attr.cancel_type = type;
    return task;
}

task_queue_t *task_queue_create(void) {
    task_queue_t *temp = (task_queue_t *) malloc(sizeof(struct task_queue));
    if (temp == NULL) {
        errno = ENOMEM;
        TR_TP_LOGE("malloc task_queue_t failed.");
        return NULL;
    }
    temp->count = 0;
    temp->tail = NULL;
    temp->head = NULL;
    temp->id = INVALID_TASK_ID;
    return temp;
}

int32_t task_queue_add_task(task_queue_t *queue, task_cancel_type cancel_type,
                            task_worker worker, task_free free, void *args) {
    TR_TP_RET_IF_NULL(queue, EINVAL)
    TR_TP_RET_IF_NULL(worker, EINVAL)
    TR_TP_RET_IF_NULL(free, EINVAL)
    task_t *new_task = task_create(queue, cancel_type, worker, free, args);
    TR_TP_RET_IF_NULL(new_task, errno)
    return task_queue_enqueue(queue, new_task);
}

task_t *task_queue_pop_task(task_queue_t *queue) {
    return task_queue_dequeue(queue);
}

int32_t task_queue_remove_task(task_queue_t *queue, task_id_t id)
{
    TR_TP_RET_IF_NULL(queue, EINVAL)
    TR_TP_RET_SET_IF((id == INVALID_TASK_ID), EINVAL, "id is invalid.", EINVAL)
    task_node_t *cur = queue->head;
    task_node_t *last = NULL;
    while (cur != NULL) {
        if (cur->task->attr.id == id) {
            break;
        }
        last = cur;
        cur = cur->next;
    }
    if (cur == NULL) {
        TR_TP_LOGE("task[%zu] not found.", id);
        return ENOENT;
    }

    if (last == NULL) { /* target node is head */
        if (queue->count == 1) {
            /* head == target node == tail, head and tail should be set to NULL */
            queue->head = NULL;
            queue->tail = NULL;
        } else {
            queue->head = cur->next;
        }
    } else {
        if (cur == queue->tail) {
            /* target == tail, tail should be changed to the previous node of target node */
            queue->tail = last;
            last->next = NULL;
        } else {
            last->next = cur->next;
        }
    }
    queue->count--;
    cur->task->free(cur->task->args);
    free(cur->task);
    free(cur);
    return EOK;
}

int32_t task_queue_enqueue(task_queue_t *queue, task_t *task) {
    TR_TP_RET_IF_NULL(queue, EINVAL)
    TR_TP_RET_IF_NULL(task, EINVAL)
    task_node_t *tmp = (task_node_t *) malloc(sizeof(task_node_t));
    if (tmp == NULL) {
        TR_TP_LOGE("malloc task_node_t failed.");
        return ENOMEM;
    }
    tmp->task = task;
    tmp->next = NULL;

    if (queue->count == 0) {
        queue->head = tmp;
        queue->tail = tmp;
    } else {
        queue->tail->next = tmp;
        queue->tail = tmp;
    }
    queue->count++;
    return EOK;
}

task_t *task_queue_dequeue(task_queue_t *queue) {
    TR_TP_RET_SET_IF((queue == NULL), EINVAL, "queue is NULL", NULL)
    TR_TP_RET_SET_IF((queue->count == 0), ENOENT, "queue is empty", NULL)
    task_node_t *head = queue->head;
    queue->head = head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    queue->count--;
    task_t *target = head->task;
    free(head);
    return target;
}

size_t task_queue_get_num(const task_queue_t *queue) {
    TR_TP_RET_SET_IF((queue == NULL), EINVAL, "queue is NULL.", 0)
    return queue->count;
}

void task_queue_clear_task(task_queue_t *queue) {
    if (queue == NULL) {
        TR_TP_LOGW("queue is null, maybe has been destroyed.");
        return;
    }
    task_node_t *cur = queue->head;
    task_node_t *last = cur;
    while (cur != NULL) {
        cur = cur->next;
        last->task->free(last->task->args);
        free(last->task);
        free(last);
        last = cur;
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->count = 0;
}

void task_queue_destroy(task_queue_t *queue) {
    if (queue == NULL) {
        TR_TP_LOGW("queue is null, maybe has been destroyed.");
        return;
    }
    task_queue_clear_task(queue);
    free(queue);
}

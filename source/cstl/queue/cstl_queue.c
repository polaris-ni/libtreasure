/*
 * @author polaris
 * @description cstl_queue.c created on 2023-12-02
 */

#include <malloc.h>
#include <errno.h>
#include "cstl_queue.h"

cstl_queue_t *cstl_queue_create(cstl_dup_func dup, cstl_free_func free) {
    if (dup == NULL || free == NULL) {
        errno = EINVAL;
        return NULL;
    }
    cstl_queue_t *queue = (cstl_queue_t *) malloc(sizeof(cstl_queue_t));
    if (queue == NULL) {
        return NULL;
    }
    queue->dup = dup;
    queue->free = free;
    queue->num = 0;
    queue->head.data = NULL;
    queue->head.next = NULL;
    queue->tail.data = NULL;
    queue->tail.next = &queue->head;
    return queue;
}

int32_t cstl_queue_enqueue(cstl_queue_t *queue, void *data) {
    if ((queue == NULL) || (queue->num == UINT32_MAX)) {
        return CSTL_ERROR;
    }
    cstl_node_t *node = malloc(sizeof(cstl_node_t));
    if (node == NULL) {
        return CSTL_ERROR;
    }
    node->data = queue->dup(data);
    if (node->data == NULL) {
        free(node);
        return CSTL_ERROR;
    }
    cstl_node_t *last = queue->tail.next;
    last->next = node;
    node->next = NULL;
    queue->tail.next = node;
    queue->num++;
    return CSTL_SUCCESS;
}

void *cstl_queue_dequeue(cstl_queue_t *queue) {
    CSTL_RET_IF_NULL_OR_EMPTY(queue, NULL)
    cstl_node_t *node = queue->head.next;
    queue->head.next = node->next;
    void *data = node->data;
    free(node);
    queue->num--;
    if (queue->num == 0) {
        queue->tail.next = &queue->head;
    }
    return data;
}

void *cstl_queue_peek(cstl_queue_t *queue) {
    CSTL_RET_IF_NULL_OR_EMPTY(queue, NULL)
    cstl_node_t *node = queue->head.next;
    void *data = node->data;
    return data;
}

void cstl_queue_destroy(cstl_queue_t *queue) {
    CSTL_RET_IF_NULL(queue,)
    cstl_node_t *node = queue->head.next;
    cstl_node_t *next;
    while (node != NULL) {
        queue->free(node->data);
        next = node->next;
        free(node);
        node = next;
    }
    free(queue);
}
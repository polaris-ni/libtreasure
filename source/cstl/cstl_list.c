/*
 * @author polaris
 * @description cstl_list.c created on 2023-12-02 
 */

#include "cstl_list.h"
#include <stddef.h>
#include <malloc.h>

struct cstl_list {
    size_t num;
    cstl_dup_func dup;
    cstl_free_func free;
    cstl_node_t *head;
    cstl_node_t *tail;
};

cstl_list_t *cstl_list_create(cstl_dup_func dup, cstl_free_func free) {
    CSTL_RET_NULL_IF_NULL(dup)
    CSTL_RET_NULL_IF_NULL(free)
    cstl_list_t *list = (cstl_list_t *) malloc(sizeof(cstl_list_t));
    CSTL_RET_NULL_IF_NULL(list);
    list->head = NULL;
    list->tail = NULL;
    list->dup = dup;
    list->free = free;
    list->num = 0;
    return list;
}

static cstl_node_t *cstl_node_create(cstl_list_t *list, const cstl_data_t *data) {
    cstl_node_t *node = (cstl_node_t *) malloc(sizeof(cstl_node_t));
    CSTL_RET_NULL_IF_NULL(node);
    if (!list->dup(data, &node->data)) {
        free(node);
        return NULL;
    }
    node->prev = NULL;
    node->next = NULL;
    return node;
}

int32_t cstl_list_add_head(cstl_list_t *list, cstl_data_t data) {
    CSTL_RET_IF_NULL(list, EINVAL);
    cstl_node_t *node = cstl_node_create(list, &data);
    CSTL_RET_IF_NULL(node, ENOMEM);
    if (list->num == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
    }
    list->num++;
    return EOK;
}

int32_t cstl_list_add_tail(cstl_list_t *list, cstl_data_t data) {
    CSTL_RET_IF_NULL(list, EINVAL);
    cstl_node_t *node = cstl_node_create(list, &data);
    CSTL_RET_IF_NULL(node, ENOMEM);
    if (list->num == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->num++;
    return EOK;
}

cstl_data_t cstl_list_pop_head(cstl_list_t *list) {
    CSTL_RET_IF_NULL_OR_EMPTY(list, CSTL_INVALID_DATA);
    cstl_node_t *node = list->head;
    list->num--;
    if (list->num == 0) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    cstl_data_t data = node->data;
    free(node);
    return data;
}

cstl_data_t cstl_list_pop_tail(cstl_list_t *list) {
    CSTL_RET_IF_NULL_OR_EMPTY(list, CSTL_INVALID_DATA);
    cstl_node_t *node = list->tail;
    list->num--;
    if (list->num == 0) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    cstl_data_t data = node->data;
    free(node);
    return data;
}

cstl_data_t cstl_list_peek_head(const cstl_list_t *list) {
    CSTL_RET_IF_NULL_OR_EMPTY(list, CSTL_INVALID_DATA);
    return list->head->data;
}

cstl_data_t cstl_list_peek_tail(const cstl_list_t *list) {
    CSTL_RET_IF_NULL_OR_EMPTY(list, CSTL_INVALID_DATA);
    return list->tail->data;
}

int32_t cstl_list_insert(cstl_list_t *list, cstl_data_t data, size_t index) {
    CSTL_RET_IF_NULL(list, EINVAL)
    if (index > list->num) {
        return EINVAL;
    }
    if (index == 0) {
        return cstl_list_add_head(list, data);
    }
    if (index == list->num) {
        return cstl_list_add_tail(list, data);
    }
    cstl_node_t *node = cstl_node_create(list, &data);
    CSTL_RET_IF_NULL(node, ENOMEM)
    cstl_node_t *target = list->head;
    for (size_t i =0; i < index; ++i) {
        target = target->next;
    }
    cstl_node_t *last = target->prev;
    node->prev = last;
    node->next = target;
    target->prev = node;
    last->next = node;
    return EOK;
}

int32_t cstl_list_remove(cstl_list_t *list, size_t index) {
    CSTL_RET_IF_NULL(list, EINVAL)
    if (index >= list->num) {
        return ENOENT;
    }
    if (index == 0) {
        (void) cstl_list_pop_head(list);
        return EOK;
    }
    if (index == list->num - 1) {
        (void) cstl_list_pop_tail(list);
        return EOK;
    }
    cstl_node_t *target = list->head;
    for (size_t i = 0; i < index; ++i) {
        target = target->next;
    }
    cstl_node_t *last = target->prev;
    last->next = target->next;
    target->next->prev = last;
    list->free(&target->data);
    free(target);
    list->num--;
    return EOK;
}

size_t cstl_list_get_num(const cstl_list_t *list) {
    return list == NULL ? 0 : list->num;
}

void cstl_list_destroy(cstl_list_t *list) {
    CSTL_RET_IF_NULL(list,)
    cstl_node_t *node = list->head;
    cstl_node_t *next = NULL;
    while (node != NULL) {
        next = node->next;
        list->free(&node->data);
        free(node);
        node = next;
    }
    free(list);
}
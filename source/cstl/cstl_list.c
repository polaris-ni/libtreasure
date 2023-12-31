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

static cstl_node_t *cstl_node_create(cstl_list_t *list, void *data) {
    cstl_node_t *node = (cstl_node_t *) malloc(sizeof(cstl_node_t));
    CSTL_RET_NULL_IF_NULL(node);
    node->data = list->dup(data);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    node->prev = NULL;
    node->next = NULL;
    return node;
}

int32_t cstl_list_add_head(cstl_list_t *list, void *data) {
    CSTL_RET_IF_NULL(list, CSTL_ERROR);
    cstl_node_t *node = cstl_node_create(list, data);
    CSTL_RET_IF_NULL(node, CSTL_ERROR);
    if (list->num == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
    }
    list->num++;
    return CSTL_SUCCESS;
}

int32_t cstl_list_add_tail(cstl_list_t *list, void *data) {
    CSTL_RET_IF_NULL(list, CSTL_ERROR);
    cstl_node_t *node = cstl_node_create(list, data);
    CSTL_RET_IF_NULL(node, CSTL_ERROR);
    if (list->num == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->num++;
    return CSTL_SUCCESS;
}

void *cstl_list_pop_head(cstl_list_t *list) {
    CSTL_RET_IF_NULL_OR_EMPTY(list, NULL);
    cstl_node_t *node = list->head;
    list->num--;
    if (list->num == 0) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    void *data = node->data;
    free(node);
    return data;
}

void *cstl_list_pop_tail(cstl_list_t *list) {
    CSTL_RET_IF_NULL_OR_EMPTY(list, NULL);
    cstl_node_t *node = list->tail;
    list->num--;
    if (list->num == 0) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    void *data = node->data;
    free(node);
    return data;
}

void *cstl_list_peek_head(const cstl_list_t *list) {
    CSTL_RET_IF_NULL_OR_EMPTY(list, NULL);
    return list->head->data;
}

void *cstl_list_peek_tail(const cstl_list_t *list) {
    CSTL_RET_IF_NULL_OR_EMPTY(list, NULL);
    return list->tail->data;
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
        list->free(node->data);
        free(node);
        node = next;
    }
    free(list);
}
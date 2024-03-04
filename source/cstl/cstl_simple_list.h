/*
 * @author polaris
 * @description cstl_simple_list.h created on 2024-03-04 
 */

#ifndef LIBTREASURE_CSTL_SIMPLE_LIST_H
#define LIBTREASURE_CSTL_SIMPLE_LIST_H

#include <stddef.h>
#include <stdbool.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"{
#endif

typedef struct cstl_list_node2 list_node_t;

struct cstl_list_node2 {
    list_node_t *prev;
    list_node_t *next;
};

#define CSTL_LIST_INIT(node) { &(node), &(node) }

static inline void cstl_list_init(list_node_t *node) {
    node->prev = node;
    node->next = node;
}

#define CSTL_LIST_ADD(p, c, n) do { \
    (c)->next = (n);                   \
    (c)->prev = (p);                   \
    (n)->prev = (c);                   \
    (p)->next = (c);                   \
} while (0)

#define CSTL_LIST_REMOVE(p, n) do { \
    (n)->prev = (p);                \
    (p)->next = (n);                \
} while (0)

static inline void cstl_list_add(list_node_t *list, list_node_t *node) {
    CSTL_LIST_ADD(list, node, list->next);
}

static inline void cstl_list_add_to_tail(list_node_t *list, list_node_t *node) {
    cstl_list_add(list->prev, node);
}

static inline void cstl_list_add_to_head(list_node_t *list, list_node_t *node) {
    cstl_list_add(list, node);
}

static inline void cstl_list_delete(list_node_t *node) {
    CSTL_LIST_REMOVE(node->prev, node->next);
    node->prev = NULL;
    node->next = NULL;
}

static inline void cstl_list_remove_tail(list_node_t *node) {
    cstl_list_delete(node->prev);
}

static inline void cstl_list_remove_head(list_node_t *node) {
    cstl_list_delete(node->next);
}

static inline bool cstl_list_is_empty(list_node_t *list) {
    return list == list->next;
}

static inline size_t cstl_list_get_size(list_node_t *list) {
    if (list == NULL) {
        return 0;
    }
    size_t cnt = 0;
    for (list_node_t *item = list->next; item != list; item = item->next) {
        cnt++;
    }

    return cnt;
}

#define cstl_list_entry(item, type, member) ((type *)((char *)item - offsetof(type, member)))

#define cstl_list_first(list, type, member) (cstl_list_is_empty(list) ? NULL : cstl_list_entry((list)->next, type, member))

#define CSTL_LIST_FOREACH(item, list, type, member) \
    for (item = cstl_list_entry((list)->next, type, member); \
         &item->member != (list);                   \
         item = cstl_list_entry(item->member.next, type, entry))


#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_SIMPLE_LIST_H */

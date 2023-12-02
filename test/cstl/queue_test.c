/*
 * @author polaris
 * @description queue_test.c created on 2023-12-02 
 */
#include <stdio.h>
#include <string.h>
#include "cstl_queue.h"
#include "cstl_default_impl.h"

static void str_cmp(char *str, char *exp) {
    printf("[%s] expect: %s current: %s\n", (str == NULL && exp == NULL) || (strcmp(str, exp) == 0) ? "PASS" : "FAIL",
           str, exp);
}

static void size_cmp(size_t item, size_t exp) {
    printf("[%s] expect: %zu current: %zu\n", (item == exp) ? "PASS" : "FAIL", item, exp);
}

void queue_test(void) {
    cstl_queue_t *queue = cstl_queue_create(cstl_string_dup, cstl_common_free);
    CSTL_RET_IF_NULL(queue,)
    cstl_queue_enqueue(queue, "0");
    size_cmp(cstl_queue_get_num(queue), 1);
    cstl_queue_enqueue(queue, "1");
    size_cmp(cstl_queue_get_num(queue), 2);
    cstl_queue_enqueue(queue, "2");
    size_cmp(cstl_queue_get_num(queue), 3);
    str_cmp((char *) cstl_queue_dequeue(queue), "0");
    str_cmp((char *) cstl_queue_dequeue(queue), "1");
    str_cmp((char *) cstl_queue_dequeue(queue), "2");
    str_cmp((char *) cstl_queue_dequeue(queue), NULL);
    size_cmp(cstl_queue_get_num(queue), 0);
    cstl_queue_enqueue(queue, "3");
    str_cmp((char *) cstl_queue_peek(queue), "3");
    size_cmp(cstl_queue_get_num(queue), 1);
    str_cmp((char *) cstl_queue_dequeue(queue), "3");
    size_cmp(cstl_queue_get_num(queue), 0);
    cstl_queue_destroy(queue);
}
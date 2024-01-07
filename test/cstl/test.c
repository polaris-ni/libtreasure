/*
 * @author polaris
 * @description queue_test.c created on 2023-12-02 
 */
#include <stdio.h>
#include <string.h>
#include "cstl_queue.h"
#include "cstl_stack.h"
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
    cstl_data_t data = {0};
    data.data = "0";
    cstl_queue_enqueue(queue, data);
    size_cmp(cstl_queue_get_num(queue), 1);
    data.data = "1";
    cstl_queue_enqueue(queue, data);
    size_cmp(cstl_queue_get_num(queue), 2);
    data.data = "2";
    cstl_queue_enqueue(queue, data);
    size_cmp(cstl_queue_get_num(queue), 3);
    str_cmp((char *) cstl_queue_dequeue(queue).data, "0");
    str_cmp((char *) cstl_queue_dequeue(queue).data, "1");
    str_cmp((char *) cstl_queue_dequeue(queue).data, "2");
    str_cmp((char *) cstl_queue_dequeue(queue).data, NULL);
    size_cmp(cstl_queue_get_num(queue), 0);
    data.data = "2";
    cstl_queue_enqueue(queue, data);
    str_cmp((char *) cstl_queue_peek(queue).data, "3");
    size_cmp(cstl_queue_get_num(queue), 1);
    str_cmp((char *) cstl_queue_dequeue(queue).data, "3");
    size_cmp(cstl_queue_get_num(queue), 0);
    cstl_queue_destroy(queue);
}

void stack_test(void) {
    cstl_stack_t *stack = cstl_stack_create(cstl_string_dup, cstl_common_free);
    CSTL_RET_IF_NULL(stack,)
    cstl_data_t data = {0};
    data.data = "0";
    cstl_stack_push(stack, data);
    size_cmp(cstl_stack_get_num(stack), 1);
    data.data = "1";
    cstl_stack_push(stack, data);
    size_cmp(cstl_stack_get_num(stack), 2);
    data.data = "2";
    cstl_stack_push(stack, data);
    size_cmp(cstl_stack_get_num(stack), 3);
    str_cmp((char *) cstl_stack_pop(stack).data, "2");
    str_cmp((char *) cstl_stack_pop(stack).data, "1");
    str_cmp((char *) cstl_stack_pop(stack).data, "0");
    str_cmp((char *) cstl_stack_pop(stack).data, NULL);
    size_cmp(cstl_stack_get_num(stack), 0);
    data.data = "3";
    cstl_stack_push(stack, data);
    str_cmp((char *) cstl_stack_peek(stack).data, "3");
    size_cmp(cstl_stack_get_num(stack), 1);
    str_cmp((char *) cstl_stack_pop(stack).data, "3");
    size_cmp(cstl_stack_get_num(stack), 0);
    cstl_stack_destroy(stack);
}
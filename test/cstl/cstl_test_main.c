/*
 * @author polaris
 * @description cstl_test_main.c created on 2023-12-02 
 */

extern void queue_test(void);

extern void stack_test(void);

#include <stdio.h>
#include <stdint.h>

int main(void) {
//    printf("%zu", sizeof(uintptr_t));
    queue_test();
    stack_test();
    return 0;
}
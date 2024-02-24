/*
 * @author polaris
 * @description cstl_test_main.c created on 2023-12-02
 */

extern void list_test(void);

extern void queue_test(void);

extern void stack_test(void);

int main(void) {
    list_test();
    queue_test();
    stack_test();
    return 0;
}
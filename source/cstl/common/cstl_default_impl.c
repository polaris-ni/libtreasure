/*
 * @author polaris
 * @description cstl_default_impl.c created on 2023-12-02 
 */

#include "cstl_default_impl.h"
#include <malloc.h>
#include <string.h>

static void *cstl_common_dup(size_t size, void *data) {
    CSTL_RET_IF_NULL(data, NULL)
    void *tmp = malloc(size);
    CSTL_RET_IF_NULL(tmp, NULL)
    (void) memcpy(tmp, data, size);
    return tmp;
}

/* e.g. char / unsigned char */
void *cstl_1byte_dup(void *data) {
    return cstl_common_dup(1, data);
}

/* e.g. short / unsigned short */
void *cstl_2byte_dup(void *data) {
    return cstl_common_dup(2, data);
}

/* e.g. int / unsigned int / float */
void *cstl_4byte_dup(void *data) {
    return cstl_common_dup(4, data);
}

/* e.g. long long int / unsigned long long int / double */
void *cstl_8byte_dup(void *data) {
    return cstl_common_dup(8, data);
}

/* for string dup */
void *cstl_string_dup(void *data) {
    CSTL_RET_IF_NULL(data, NULL)
    return cstl_common_dup(strlen(data), data);
}

/* just call free */
void cstl_common_free(void *data) {
    free(data);
}

/*
 * @author polaris
 * @description cstl_default_impl.c created on 2023-12-02 
 */

#include "cstl_default_impl.h"
#include <malloc.h>
#include <string.h>

void *cstl_common_dup(size_t size, void *data) {
    CSTL_RET_NULL_IF_NULL(data)
    void *tmp = malloc(size);
    CSTL_RET_NULL_IF_NULL(tmp)
    (void) memcpy((void *) tmp, (const void *) data, size);
    return tmp;
}

/* for string dup */
void *cstl_string_dup(void *data) {
    CSTL_RET_NULL_IF_NULL(data)
    return cstl_common_dup(strlen((void *) data) + 1, data);
}

/* just call free */
void cstl_common_free(void *data) {
    free((void *) data);
}

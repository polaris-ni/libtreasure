/*
 * @author polaris
 * @description cstl_default_impl.h created on 2023-12-02
 */

#ifndef LIBTREASURE_CSTL_DEFAULT_IMPL_H
#define LIBTREASURE_CSTL_DEFAULT_IMPL_H

#include "cstl_defines.h"
#include <stddef.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

void *cstl_common_dup(void *data, size_t size);

/* for string dup */
bool cstl_string_dup(const cstl_data_t *src, cstl_data_t *dest);

/* just call free */
void cstl_common_free(cstl_data_t *data);

/* just return itself */
bool cstl_not_dup(const cstl_data_t *src, cstl_data_t *dest);

/* do nothing on free */
void cstl_not_free(cstl_data_t *data);

/* murmurhash impl, as default hashmap hash func */
uint64_t cstl_murmurhash(const void *data, size_t size);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_DEFAULT_IMPL_H */

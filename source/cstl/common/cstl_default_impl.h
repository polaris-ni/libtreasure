/*
 * @author polaris
 * @description cstl_default_impl.h created on 2023-12-02 
 */

#ifndef LIBTREASURE_CSTL_DEFAULT_IMPL_H
#define LIBTREASURE_CSTL_DEFAULT_IMPL_H

#include "cstl_defines.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"{
#endif

/* e.g. char / unsigned char */
void *cstl_1byte_dup(void *data);

/* e.g. short / unsigned short */
void *cstl_2byte_dup(void *data);

/* e.g. int / unsigned int / float */
void *cstl_4byte_dup(void *data);

/* e.g. long long int / unsigned long long int / double */
void *cstl_8byte_dup(void *data);

/* for string dup */
void *cstl_string_dup(void *data);

/* just call free */
void cstl_common_free(void *data);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_DEFAULT_IMPL_H */

/*
 * @author polaris
 * @description cstl_map.h created on 2023-12-15 
 */

#ifndef LIBTREASURE_CSTL_MAP_H
#define LIBTREASURE_CSTL_MAP_H

#include "cstl_defines.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"{
#endif

typedef struct cstl_entry {
    void *key;
    void *value;
} cstl_entry_t;

typedef struct cstl_dup_free {
    cstl_dup_func dup;
    cstl_free_func free;
} cstl_func_pair;

typedef struct cstl_map {
    cstl_func_pair key_func;
    cstl_func_pair value_func;
} cstl_map_t;

cstl_map_t *cstl_hashmap_create(cstl_func_pair key_func, cstl_func_pair value_func);

int32_t cstl_hashmap_put(cstl_map_t *map, void *key, void *value);

void *cstl_hashmap_get(cstl_map_t *map, void *key);

void cstl_hashmap_destroy(cstl_map_t *map);


#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_MAP_H */

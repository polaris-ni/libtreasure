/*
 * @author polaris
 * @description cstl_map.h created on 2023-12-15 
 */

#ifndef LIBTREASURE_CSTL_MAP_H
#define LIBTREASURE_CSTL_MAP_H

#include "cstl_defines.h"
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"{
#endif

typedef struct cstl_entry cstl_entry_t;

struct cstl_entry {
    void *key;
    void *value;
    cstl_entry_t *next;
};

typedef uint64_t (*cstl_hash_func)(const void *key);

typedef size_t (*cstl_size_func)(const void *data);

typedef bool (*cstl_key_equal_func)(const void *key1, const void *key2);

typedef struct cstl_dup_free {
    cstl_dup_func dup;
    cstl_free_func free;
} cstl_func_pair;

typedef struct cstl_map {
    size_t capacity;
    size_t num;
    cstl_entry_t *entries;
    cstl_size_func key_size;
    cstl_hash_func hash;
    cstl_key_equal_func equals;
    cstl_func_pair key_func;
    cstl_func_pair value_func;
} cstl_map_t;

cstl_map_t *cstl_hashmap_create(cstl_hash_func hash,
                                cstl_key_equal_func equals,
                                cstl_size_func key_size,
                                cstl_func_pair key_func,
                                cstl_func_pair value_func);

int32_t cstl_hashmap_put(cstl_map_t *map, void *key, void *value);

void *cstl_hashmap_get(cstl_map_t *map, void *key);

int32_t cstl_hashmap_remove(cstl_map_t *map, void *key);

void cstl_hashmap_destroy(cstl_map_t *map);


#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_CSTL_MAP_H */

/*
 * @author polaris
 * @description cstl_map.c created on 2023-12-15 
 */

#include "cstl_map.h"
#include <malloc.h>

cstl_map_t *cstl_hashmap_create(cstl_hash_func hash,
                                cstl_key_equal_func equals,
                                cstl_func_pair key_func,
                                cstl_func_pair value_func) {
    cstl_map_t *map = (cstl_map_t *) malloc(sizeof(cstl_map_t));
    CSTL_RET_NULL_IF_NULL(map)
    map->key_func.dup = key_func.dup;
    map->key_func.free = key_func.free;
    map->value_func.dup = value_func.dup;
    map->value_func.free = value_func.free;
    map->hash = hash;
    map->equals = equals;
    return map;
}
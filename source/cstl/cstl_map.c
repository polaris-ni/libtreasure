/*
 * @author polaris
 * @description cstl_map.c created on 2023-12-15 
 */

#include "cstl_map.h"
#include <malloc.h>

#ifndef CSTL_HASHMAP_MAX_CAPACITY
#define CSTL_HASHMAP_MAX_CAPACITY 256
#endif

#ifndef CSTL_HASHMAP_RESIZE_THRESHOLD
#define CSTL_HASHMAP_RESIZE_THRESHOLD 0.75
#endif

struct cstl_entry {
    void *key;
    void *value;
    cstl_entry_t *next;
};

struct cstl_map {
    size_t capacity;
    size_t num;
    cstl_entry_t *entries;
    cstl_size_func key_size;
    cstl_hash_func hash;
    cstl_key_equal_func equals;
    cstl_func_pair key_func;
    cstl_func_pair value_func;
};

cstl_map_t *cstl_hashmap_create(cstl_hash_func hash,
                                cstl_key_equal_func equals,
                                cstl_size_func key_size,
                                cstl_func_pair key_func,
                                cstl_func_pair value_func) {
    cstl_map_t *map = (cstl_map_t *) malloc(sizeof(cstl_map_t));
    CSTL_RET_NULL_IF_NULL(map)
    map->capacity = 16;
    map->entries = malloc(sizeof(cstl_entry_t) * map->capacity);
    if (map->entries == NULL) {
        free(map);
        return NULL;
    }
    map->key_func.dup = key_func.dup;
    map->key_func.free = key_func.free;
    map->value_func.dup = value_func.dup;
    map->value_func.free = value_func.free;
    map->key_size = key_size;
    map->hash = hash;
    map->equals = equals;
    return map;
}

static cstl_entry_t *find_entry_by_key(cstl_map_t *map, bool create, const void *key) {
    uint64_t index = map->hash(key) % map->capacity;
    if (map->entries[index].key == NULL) {
        return &map->entries[index];
    }
    cstl_entry_t *current = &map->entries[index];
    cstl_entry_t *last = current;
    while (current != NULL) {
        if (map->equals(current->key, key)) {
            return current;
        }
        last = current;
        current = current->next;
    }
    if (!create) {
        return NULL;
    }
    cstl_entry_t *tmp = malloc(sizeof(cstl_entry_t));
    CSTL_RET_NULL_IF_NULL(tmp);
    tmp->key = NULL;
    tmp->value = NULL;
    tmp->next = NULL;
    last->next = tmp;
    return tmp;
}

int32_t cstl_hashmap_put(cstl_map_t *map, void *key, void *value) {
    CSTL_RET_IF_NULL(map, CSTL_BAD_PARAMS)
    CSTL_RET_IF_NULL(key, CSTL_BAD_PARAMS)
    CSTL_RET_IF_NULL(value, CSTL_BAD_PARAMS)
    void *tmp_key = map->key_func.dup(key);
    CSTL_RET_IF_NULL(tmp_key, CSTL_ERROR)
    void *tmp_value = map->value_func.dup(value);
    if (tmp_value == NULL) {
        map->key_func.free(tmp_key);
        return CSTL_ERROR;
    }
    cstl_entry_t *entry = find_entry_by_key(map, true, tmp_key);
    if (entry == NULL) {
        map->key_func.free(tmp_key);
        map->value_func.free(tmp_value);
        return CSTL_ERROR;
    }
    entry->key = tmp_key;
    entry->value = tmp_value;
    return CSTL_SUCCESS;
}

void *cstl_hashmap_get(cstl_map_t *map, void *key) {
    CSTL_RET_NULL_IF_NULL(map)
    CSTL_RET_NULL_IF_NULL(key)
    cstl_entry_t *entry = find_entry_by_key(map, false, key);
    CSTL_RET_NULL_IF_NULL(entry)
    return entry->value;
}

int32_t cstl_hashmap_remove(cstl_map_t *map, void *key) {
    CSTL_RET_IF_NULL(map, CSTL_BAD_PARAMS)
    CSTL_RET_IF_NULL(key, CSTL_BAD_PARAMS)
    uint64_t index = map->hash(key) % map->capacity;
    cstl_entry_t *current = &map->entries[index];
    cstl_entry_t *last = NULL;
    while (current != NULL) {
        if (map->equals(current->key, key)) {
            break;
        }
        last = current;
        current = current->next;
    }
    CSTL_RET_IF_NULL(current, CSTL_ITEM_NOT_FOUND)
    map->key_func.free(current->key);
    map->value_func.free(current->value);
    if (last == NULL) {
        if (current->next == NULL) {
            return CSTL_SUCCESS;
        }
        cstl_entry_t *next = current->next;
        current->key = next->key;
        current->value = next->value;
        current->next = next->next;
        free(next);
        return CSTL_SUCCESS;
    } else {
        last->next = current->next;
        free(current);
        return CSTL_SUCCESS;
    }
}

static void clear_entry(cstl_map_t *map, cstl_entry_t *entry) {
    map->key_func.free(entry);
    map->value_func.free(entry);
    entry->key = NULL;
    entry->value = NULL;
}

static void delete_entry(cstl_map_t *map, cstl_entry_t *entry) {
    clear_entry(map, entry);
    free(entry);
}

static void delete_entry_recursively(cstl_map_t *map, cstl_entry_t *entry) {
    cstl_entry_t *current = entry;
    cstl_entry_t *next = NULL;
    while (current != NULL) {
        next = current->next;
        clear_entry(map, current);
        current = next;
    }
}

void cstl_hashmap_destroy(cstl_map_t *map) {
    CSTL_RET_IF_NULL(map,)
    for (size_t i = 0; i < map->capacity; ++i) {
        delete_entry_recursively(map, map->entries[i].next);
        clear_entry(map, &map->entries[i]);
    }
    free(map->entries);
    free(map);
}
/*
 * @author polaris
 * @description cstl_default_impl.c created on 2023-12-02
 */

#include "cstl_default_impl.h"
#include <malloc.h>
#include <string.h>

void *cstl_common_dup(void *data, size_t size) {
    CSTL_RET_NULL_IF_NULL(data)
    void *tmp = malloc(size);
    CSTL_RET_NULL_IF_NULL(tmp)
    (void) memcpy((void *) tmp, (const void *) data, size);
    return tmp;
}

/* for string dup */
bool cstl_string_dup(const cstl_data_t *src, cstl_data_t *dest) {
    dest->data = cstl_common_dup(src->data, strlen((void *) src->data) + 1);
    return dest->data != NULL;
}

/* just call free */
void cstl_common_free(cstl_data_t *data) { free(data->data); }

bool cstl_not_dup(const cstl_data_t *src, cstl_data_t *dest) {
    return memcpy(dest, src, sizeof(cstl_data_t)) == src;
}

void cstl_not_free(CSTL_UNUSED cstl_data_t *data) {}

#define CSTL_MURMURHASH_VC1 0xCC9E2D51
#define CSTL_MURMURHASH_VC2 0x1B873593
#define CSTL_MURMURHASH_HC1 0xE6546B64
#define CSTL_MURMURHASH_HC2 0x85EBCA6B
#define CSTL_MURMURHASH_HC3 0xC2B2AE35
#define CSTL_MURMURHASH_HC4 5
#define CSTL_MURMURHASH_SEED 0x3B9ACA07 /* 1000000007 */
#define CSTL_MURMURHASH_V_ROTATE 15
#define CSTL_MURMURHASH_H_ROTATE 13
#define CSTL_MURMURHASH_CHAR_FOR_PER_LOOP 4
#define CSTL_MURMURHASH_SHIFT8 8
#define CSTL_MURMURHASH_SHIFT13 13
#define CSTL_MURMURHASH_SHIFT16 16
#define CSTL_MURMURHASH_SHIFT24 24

static size_t murmurhash_rotate(size_t v, uint32_t offset) {
    return ((v << offset) | (v >> (sizeof(size_t) * 8 - offset)));
}

static size_t murmurhash_mix_v(size_t v) {
    v = v * CSTL_MURMURHASH_VC1;
    v = murmurhash_rotate(v, CSTL_MURMURHASH_V_ROTATE);
    v = v * CSTL_MURMURHASH_VC2;
    return v;
}

static size_t murmurhash_mix_h(size_t h, size_t v) {
    size_t res = h;
    res ^= v;
    res = murmurhash_rotate(res, CSTL_MURMURHASH_H_ROTATE);
    res = res * CSTL_MURMURHASH_HC4 + CSTL_MURMURHASH_HC1;
    return res;
}

uint64_t cstl_murmurhash(const void *data, size_t size) {
    const uint8_t *tmp = (const uint8_t *) data;
    size_t i = 0;
    size_t v;
    size_t h = CSTL_MURMURHASH_SEED;
    uint8_t c0, c1, c2, c3;
    size_t tmp_len = size - size % CSTL_MURMURHASH_CHAR_FOR_PER_LOOP;
    while ((i + CSTL_MURMURHASH_CHAR_FOR_PER_LOOP) <= tmp_len) {
        c0 = tmp[i++];
        c1 = tmp[i++];
        c2 = tmp[i++];
        c3 = tmp[i++];
        v = (size_t) c0 | ((size_t) c1 << CSTL_MURMURHASH_SHIFT8) |
            ((size_t) c2 << CSTL_MURMURHASH_SHIFT16) |
            ((size_t) c3 << CSTL_MURMURHASH_SHIFT24);
        v = murmurhash_mix_v(v);
        h = murmurhash_mix_h(h, v);
    }

    v = 0;
    switch (size & 3) {
        case 3:
            v ^= ((size_t) tmp[i + 2] << CSTL_MURMURHASH_SHIFT16);
        case 2:
            v ^= ((size_t) tmp[i + 2] << CSTL_MURMURHASH_SHIFT8);
        case 1:
            v ^= tmp[i];
            v = murmurhash_mix_v(v);
            h ^= v;
            break;
        default:
            break;
    }
    h ^= h >> CSTL_MURMURHASH_SHIFT16;
    h *= CSTL_MURMURHASH_HC2;
    h ^= h >> CSTL_MURMURHASH_SHIFT13;
    h *= CSTL_MURMURHASH_HC3;
    h ^= h >> CSTL_MURMURHASH_SHIFT16;
    return h;
}

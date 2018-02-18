#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "vec.h"

// vector contains generic pointer
vec_t
vec_new() {
    vec_t v = (vec_t)calloc(1, sizeof(struct _vector));
    if (v) {
        v->reserved = 8;
        v->items = (voidptr_t)calloc(v->reserved, sizeof(voidptr_t));
        v->length = 0;
    }
    return v;
}

void
vec_free(vec_t *_v) {
    vec_t v = *_v;
    if (v) {
        free(v->items);
        v->items = NULL;
    }
    free(v);
    *_v = (vec_t)NULL;
}

bool
vec_reserve(vec_t v, uint64_t reserve) {
    if (v->length > reserve)
        return false;
    voidptr_t *new_items = (voidptr_t )realloc(v->items, sizeof(voidptr_t ) * reserve);
    if (new_items==NULL)
        return false;
    v->items = new_items;
    v->reserved = reserve;
    if (v->reserved > v->length) {
        uint64_t diff = v->reserved - v->length;
        memset(v->items + v->length, 0, sizeof(voidptr_t) * diff);
    }
    return true;
}

bool
vec_push(vec_t v, voidptr_t item) {
    if (v->reserved == v->length) {
        uint64_t reserve = v->length * 2;
        if (!vec_reserve(v, reserve))
            return false;
    }
    v->items[v->length] = item;
    v->length++;
    return true;
}

bool
vec_del(vec_t v, uint64_t idx) {
    if (v->length <= idx)
        return false;

    for (uint64_t i = idx; i < v->length -1; i++)
        v->items[i] = v->items[i+1];
    v->items[v->length-1] = 0;
    v->length --;
    return true;
}

voidptr_t
vec_get(vec_t v, uint64_t idx) {
    voidptr_t item = NULL;
    if (v->length > idx) {
        item = v->items[idx];
    }
    return item;
}

voidptr_t
vec_pop(vec_t v) {
    if (v->length == 0)
        return NULL;
    uint64_t idx = v->length-1;
    voidptr_t item = vec_get(v, idx);
    if (item && !vec_del(v, idx))
        return NULL;
    return item;
}


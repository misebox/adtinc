#include <stdlib.h>
#include <stdbool.h>
#include "general.h"


struct _vec {
    uint64_t reserved;
    uint64_t length;
    voidptr_t *items;
};
typedef struct _vec vec_t;
typedef vec_t *pvec;

pvec
    vec_new();

void
    vec_free(pvec *v);

bool
    vec_reserve(pvec v, uint64_t reserve);

bool
    vec_push(pvec v, voidptr_t item);

bool
    vec_insert(pvec v, voidptr_t item, uint64_t pos);

bool
    vec_del(pvec v, uint64_t idx);

voidptr_t
    vec_get(pvec v, uint64_t idx);

voidptr_t
    vec_pop(pvec v);

pvec
    vec_copy(pvec v);

pvec
    vec_copy_slice(pvec v, uint64_t start, uint64_t end);

bool
    vec_find_ptr(pvec v, uint64_t *idx, voidptr_t target);

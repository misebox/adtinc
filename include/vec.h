#include <stdlib.h>
#include <stdbool.h>


#define DEBUG(msg) printf("File: %s, Func: %s, Line: %d, Msg: %s\n", __FILE__, __FUNCTION__, __LINE__, msg);


typedef void *voidptr_t;

struct _vector {
    uint64_t reserved;
    uint64_t length;
    voidptr_t *items;
};
typedef struct _vector *vec_t;

vec_t
    vec_new();

void
    vec_free(vec_t *v);

bool
    vec_reserve(vec_t v, uint64_t reserve);

bool
    vec_add(vec_t v, voidptr_t item);

bool
    vec_del(vec_t v, uint64_t idx);

voidptr_t
    vec_get(vec_t v, uint64_t idx);

voidptr_t
    vec_pop(vec_t v, uint64_t idx);


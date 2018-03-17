#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "dict.h"

// dict hash map

uint64_t
dict_hash(pu8 key, dict_size_t frame) {
    assert(frame > 0);
    uint64_t hashed = 0;
    for (u8size_t i = 0; i < key->size -1; i++) {
        hashed += key->bytes[i];
    }
    hashed %= frame;
    return hashed;
}

pdict
dict_new(dict_size_t size) {
    assert(size > 0);
    pdict pd = (pdict)calloc(1, sizeof(dict_t));
    pd->items = (pdict_item)calloc(size, sizeof(dict_item_t));
    pd->size = size;
    pd->count = 0;
    return pd;
}

void
dict_free(pdict *pd) {
    free((*pd)->items);
    free(*pd);
    *pd = NULL;
}


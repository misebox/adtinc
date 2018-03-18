#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "dict.h"

// dict hash map

bool is_prime(int n) {
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    int divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= n) {
        if (n % (divisor - 1) == 0 || n % (divisor + 1) == 0)
            return false;
        divisor += 6;
    }
    return true;
}

uint64_t nextprime(uint32_t a) {
    while (!is_prime(++a)) {}
    return a;
}

dict_size_t
dict_hash(pu8 key, dict_size_t size) {
    assert(size > 0);
    uint64_t hashed = 0;
    for (u8size_t i = 0; i < key->size -1; i++) {
        hashed += key->bytes[i];
    }
    hashed %= size;
    return hashed;
}

pdict
dict_new(dict_size_t size) {
    pdict pd = (pdict)calloc(1, sizeof(dict_t));
    if (pd == NULL)
        return NULL;
    pd->items = (pdict_item)calloc(size, sizeof(dict_item_t));
    if (pd->items == NULL) {
        free(pd);
        return NULL;
    }
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

dict_size_t
dict_set(pdict d, pu8 k, voidptr_t v) {
    assert(k != NULL);
    if (d->count > (d->size * dict_threshold)) {
        // Rehash with expanded size
        dict_size_t target_size = d->size * 2 <= dict_max_size ? d->size * 2 : dict_max_size;
        assert(dict_rehashed(d, target_size));
    }
    dict_size_t ideal = dict_hash(k, d->size);
    for (dict_size_t i = 0; i < d->size; i++) {
        dict_size_t addr = (ideal + i) % d->size;
        pdict_item slot = d->items + addr;
        if (slot->key == NULL) {
            // set ok
            d->count ++;
            slot->hash = ideal;
            slot->key = k;
            slot->value = v;
            return addr;
        } else if (u8_eq(k, slot->key)) {
            // overwrite
            slot->hash = ideal;
            slot->value = v;
            return addr;
        }
    }
    assert(false);
}

bool
dict_addr_from_key(pdict d, pu8 k, dict_size_t *actual) {
    assert(k != NULL);
    dict_size_t ideal = dict_hash(k, d->size);
    for (dict_size_t i = 0; i < d->size; i++) {
        dict_size_t addr = (ideal + i) % d->size;
        pdict_item slot = d->items + addr;
        if (slot->key && u8_eq(k, slot->key)) {
            // found
            *actual = addr;
            return true;
        }
    }
    // not found
    return false;
}

voidptr_t
dict_get(pdict d, pu8 k) {
    dict_size_t actual = 0;
    if (dict_addr_from_key(d, k, &actual)) {
        return (d->items + actual)->value;
    }
    return NULL;
}

bool
dict_has_key(pdict d, pu8 k) {
    dict_size_t actual = 0;
    return dict_addr_from_key(d, k, &actual);
}

bool
dict_rehashed(pdict d, dict_size_t size) {
    assert(size > d->count);
    pdict_item rehashed = (pdict_item)calloc(size, sizeof(dict_item_t));
    if (rehashed == NULL) {
        return false;
    }
    // replace items
    pdict_item src_items = d->items;
    d->items = rehashed;
    dict_size_t src_size = d->size;
    d->size = size;
    d->count = 0;
    for (dict_size_t i = 0; i < src_size; i++) {
        pdict_item slot = src_items + i;
        if (slot->key != NULL)
            dict_set(d, slot->key, slot->value);
    }
    free(src_items);
    return true;
}

bool
dict_delete(pdict d, pu8 k) {
    dict_size_t actual = 0;
    if (!dict_addr_from_key(d, k, &actual)) {
        return false;
    }
    pdict_item slot = d->items + actual;
    slot->hash = 0;
    slot->key = NULL;
    slot->value = NULL;
    d->count --;
    return true;
}

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <assert.h>

#include "dict.h"


static char *fruits[] = {
    "Apple",
    "Banana",
    "Cherry",
    "Dates",
};

void
show_dict(pdict d) {
    printf("dict: %p (count: %3u, size: %3u)\n", d, d->count, d->size);
    for (dict_size_t i = 0; i < d->size; i++) {
        pdict_item slot = (d->items + i);
        if (slot->key != NULL)
            printf("[hash: %u, key: %s, value: %p (%s)]\n", slot->hash, slot->key->bytes, slot->value, slot->value);
    }
}


int main() {
    for (dict_size_t size = 16; size <= 256; size <<= 1) {
        for (uint8_t i = 0; i < 4; i++) {
            pu8 fruit = u8_new(fruits[i]);
            printf("(key=[%6s], size=[%3u]: %3u) ", (const char *)fruit->bytes, size, dict_hash(fruit, size));
            u8_free(&fruit);
        }
        printf("\n");
    }
    pdict pd = dict_new(100);
    pu8 key1 = u8_new("This is a key.");
    pu8 key2 = u8_new("This is a key.2222");
    dict_size_t addr1 = dict_set(pd, key1, (voidptr_t)"apple");
    dict_size_t addr2 = dict_set(pd, key2, (voidptr_t)"banana");
    const char *val1 = dict_get(pd, key1);
    const char *val2 = dict_get(pd, key2);
    show_dict(pd);
    u8_free(&key1);
    u8_free(&key2);
    dict_free(&pd);

    return 0;
}

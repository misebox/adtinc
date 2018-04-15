#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <assert.h>

#include "adt.h"


static const char *keys[] = { // 16
    "kApple",
    "kApricot",
    "kAvocado",
    "kBanana",
    "kBilberry",
    "kBlackberry",
    "kBlackcurrant",
    "kBlueberry",
    "kBoysenberry",
    "kCrab apples",
    "kCurrant",
    "kCherry",
    "kCherimoya",
    "kChico fruit",
    "kCloudberry",
    "kCoconut",
};

static const char *values[] = { // 16
    "vApple",
    "vApricot",
    "vAvocado",
    "vBanana",
    "vBilberry",
    "vBlackberry",
    "vBlackcurrant",
    "vBlueberry",
    "vBoysenberry",
    "vCrab apples",
    "vCurrant",
    "vCherry",
    "vCherimoya",
    "vChico fruit",
    "vCloudberry",
    "vCoconut",
};
void
show_dict(pdict d) {
    printf("dict: %p (count: %3u, size: %3u)\n", d, d->count, d->size);
    for (dict_size_t i = 0; i < d->size; i++) {
        pdict_item slot = (d->items + i);
        if (slot->key != NULL)
            printf("[addr: %u, hash: %u, key: %s, value: %p (%s)]\n", i, slot->hash, slot->key->bytes, slot->value, slot->value);
    }
}


int main() {
    for (dict_size_t size = 16; size <= 256; size <<= 1) {
        for (uint8_t i = 0; i < 4; i++) {
            pu8 fruit = u8_new(keys[i]);
            printf("(key=[%6s], size=[%3u]: %3u) ", (const char *)fruit->bytes, size, dict_hash(fruit, size));
            u8_free(&fruit);
        }
        printf("\n");
    }

    pdict pd = dict_new(10);
    pu8 u8keys[16];
    for (dict_size_t i = 0; i < 16; i++) {
        pu8 key = u8_new(keys[i]);
        u8keys[i] = key;
        dict_set(pd, key, (voidptr_t)values[i]);
    }
    show_dict(pd);
    for (dict_size_t i = 0; i < 16; i++) {
        assert(dict_delete(pd, u8keys[i]));
    }
    for (dict_size_t i = 0; i < 16; i++) {
        u8_free(&(u8keys[i]));
    }

    dict_free(&pd);

    return 0;
}

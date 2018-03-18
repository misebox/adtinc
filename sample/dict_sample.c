#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <assert.h>

#include "dict.h"


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
    pdict pd = dict_new(16);
    pu8 key1 = u8_new("This is first key.");
    pu8 key2 = u8_new("This is second key.");
    pu8 key3 = u8_new("This is first key.2222");
    pu8 key4 = u8_new("This is first key.");
    dict_size_t addr1 = dict_set(pd, key1, (voidptr_t)"apple");
    dict_size_t addr2 = dict_set(pd, key2, (voidptr_t)"banana");
    dict_size_t addr3 = dict_set(pd, key3, (voidptr_t)"cherry");
    dict_size_t addr4 = dict_set(pd, key4, (voidptr_t)"dates");
    const char *val1 = dict_get(pd, key1);
    const char *val2 = dict_get(pd, key2);
    const char *val3 = dict_get(pd, key3);
    show_dict(pd);
    assert(dict_rehashed(pd, 20));
    show_dict(pd);
    u8_free(&key1);
    u8_free(&key2);
    dict_free(&pd);

    pd = dict_new(16);
    pu8 u8keys[16];
    for (dict_size_t i = 0; i < 16; i++) {
        pu8 key = u8_new(keys[i]);
        u8keys[i] = key;
        dict_set(pd, key, (voidptr_t)values[i]);
    }
    show_dict(pd);
    for (dict_size_t i = 0; i < 16; i++)
        u8_free(&(u8keys[i]));
    dict_free(&pd);

    return 0;
}

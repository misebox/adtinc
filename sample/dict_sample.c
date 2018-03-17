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
    "Elderberry",
};

int main() {
    for (dict_size_t size = 1; size <= 256; size++) {
        for (uint8_t i = 0; i < 5; i++) {
            pu8 fruit = u8_new(fruits[i]);
            printf("key=[%s], size=[%u]: %llu\n", (const char *)fruit->bytes, size, dict_hash(fruit, size));
            u8_free(&fruit);
        }
    }
    return 0;
}

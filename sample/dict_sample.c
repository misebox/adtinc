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

int main() {
    for (dict_size_t size = 16; size <= 256; size <<= 1) {
        for (uint8_t i = 0; i < 4; i++) {
            pu8 fruit = u8_new(fruits[i]);
            printf("(key=[%6s], size=[%3u]: %3u) ", (const char *)fruit->bytes, size, dict_hash(fruit, size));
            u8_free(&fruit);
        }
        printf("\n");
    }
    return 0;
}

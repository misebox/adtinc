#include <stdio.h>
#include <stdbool.h>
#include "vec.h"

void show_item(vec_t v, uint64_t idx) {
    uint64_t item =  *(uint64_t *)vec_get(v, idx);
    printf("length: %2llu, reserved: %2llu, value: %3llu\n", v->length, v->reserved, item);
}

int main() {
    vec_t v = vec_new();
    uint64_t items[17];
    for (uint64_t i = 0; i<17; i++) {
        items[i] = i * 10;
        if (vec_add(v, &items[i]))
            show_item(v, i);
        else
            printf("failed");
    }
    return 0;
}


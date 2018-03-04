#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "vec.h"
#include "u8.h"

void show_item(vec_t v, uint64_t idx) {
    uint64_t item =  *(uint64_t *)vec_get(v, idx);
    printf("length: %2llu, reserved: %2llu, value: %3llu, ptr: %p\n", v->length, v->reserved, item, v->items[idx]);
}

uint8_t aaa(int16_t a) {
    return a;
}
int main() {
    vec_t v = vec_new();
    uint64_t items[0x100000];
    for (uint64_t i = 0; i<0x100000; i++)
        items[i] = i * 10;

    for (uint64_t i = 0; i<0x100000; i++)
        if (!vec_push(v, &items[i]))
            printf("failed");

    for (uint64_t i = 0; i<9; i++)
        show_item(v, i);


    uint64_t idx;
    printf("target:%p\n", &items[0xff]);
    clock_t start,end;
    start = clock();
    bool found = vec_find_ptr(v, &idx, &items[0xff]);
    end = clock();
    if (found)
        printf("found! %llu\n", idx);
    printf("%.6f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);

    vec_free(&v);
    uint16_t m = 11;
    for (uint16_t i = 0; i< 16; i++)
        printf("%d: %d\n", i, m *= 13);

    const char *str = u8"abcde αβγδεζη あいうえお 🍣🍺🍀";
    printf("string: [%s], length:%d\n", str, u8_length(str));
    char s[2];
    s[0] = 0x80;
    s[1] = 0;
    printf("%u\n", u8_length(s));
    printf("%s %lu %u\n", u8"🍣🍺🍀", strlen(u8"🍣🍺🍀"),  u8_length(u8"🍣🍺🍀"));
    return 0;
}


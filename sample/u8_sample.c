#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "vec.h"
#include "u8.h"


int main() {
    const char *str = u8"abcde αβγδεζη あいうえお 🍣🍺🍀";
    printf("string: [%s], length:%d\n", str, u8_length(str));
    char s[2];
    s[0] = 0x80;
    s[1] = 0;
    printf("%u\n", u8_length(s));
    printf("%s %lu %u\n", u8"🍣🍺🍀", strlen(u8"🍣🍺🍀"),  u8_length(u8"🍣🍺🍀"));

    pvec lst = vec_new();
    vec_push(lst, u8_new(u8"過去が現在に影響を与えるように、未来も現在に影響を与える。"));
    vec_push(lst, u8_new(u8"「なぜ生きるか🍺」を知っている者は、ほとんど、あらゆる「いかに生きるか🍺」に耐えるのだ。"));
    vec_push(lst, u8_new(u8"樹木🍀にとって最も大切なものは何かと問うたら、それは果実だと誰もが答えるだろう。しかし実際には種なのだ。"));
    vec_push(lst, u8_new(u8"あなたが出会う最悪の敵🍣は、いつもあなた自身🍣であるだろう。"));
    pu8 sliced = u8_new("");
    for (u8size_t i=0; i < lst->length; i++) {
        pu8 u = vec_get(lst, i);
        printf("%s\n", u->bytes);
        if (u8_slice(sliced, u, 1, -1))
            printf("sliced: [%s], length: %u, size: %u, reserved: %u\n", sliced->bytes, sliced->length, sliced->size, sliced->reserved);
    }
    for (u8size_t i=0; i < lst->length; i++) {
        pu8 u = vec_get(lst, i);
        u8_free(&u);
    }
    vec_free(&lst);


    pu8 src = u8_new(u8"🍣🍣🍣🍺🍺🍺");
    pu8 dst = u8_new(u8"");
    if (u8_slice(dst, src, 2, 4)) printf("%s\n", dst->bytes); // 🍣🍺
    if (u8_slice(dst, src, 1, -1)) printf("%s\n", dst->bytes); // 🍣🍣🍺🍺
    u8_free(&src);
    u8_free(&dst);
    return 0;
}


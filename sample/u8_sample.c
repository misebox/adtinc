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

    vec_t lst = vec_new();
    vec_push(lst, u8_new(u8"過去が現在に影響を与えるように、未来も現在に影響を与える。"));
    vec_push(lst, u8_new(u8"「なぜ生きるか🍺」を知っている者は、ほとんど、あらゆる「いかに生きるか🍺」に耐えるのだ。"));
    vec_push(lst, u8_new(u8"樹木🍀にとって最も大切なものは何かと問うたら、それは果実だと誰もが答えるだろう。しかし実際には種なのだ。"));
    vec_push(lst, u8_new(u8"あなたが出会う最悪の敵🍣は、いつもあなた自身🍣であるだろう。"));
    for (u8size_t i=0; i < lst->length; i++) {
        u8_t u = vec_get(lst, i);
        printf("%s\n", u->bytes);
    }
    for (u8size_t i=0; i < lst->length; i++) {
        u8_t u = vec_get(lst, i);
        u8_free(&u);
    }
    vec_free(&lst);
    return 0;
}


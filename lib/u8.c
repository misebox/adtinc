#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "u8.h"

// utf-8 string
u8size_t
u8_length(const char *s) {
    u8size_t length = 0;
    for(const char *max = s + u8_maxlength; *s != '\0'; length++) {
        uint8_t c = *s & 0xFF;
        if ((0x80 <= c && c <= 0xC1)
            || (0xF5 <= c)
            || (uintptr_t)s >= (uintptr_t)max
        ) {
            // Found an invalid byte or exceeded max length
            length = u8_none;
            break;
        }
        // Forward pointer to next character
        s +=  ((c & 0x80) == 0)
            + ((c & 0xE0) == 0xC0) * 2
            + ((c & 0xF0) == 0xE0) * 3
            + ((c & 0xF8) == 0xF0) * 4;
    }
    return length;
}
//u8_t
//u8_new() {
//    u8_t u = (u8_t)calloc(1, sizeof(struct _u8));
//    if (u) {
//        u->reserved = 8;
//        u->bytes = (uint8ptr_t)calloc(u->reserved, sizeof(uint8ptr_t));
//        u->length = 0;
//    }
//    return u;
//}
//
//void
//u8_free(u8_t *_u) {
//    u8_t u = *_u;
//    if (u) {
//        free(u->bytes);
//        u->bytes = NULL;
//    }
//    free(u);
//    *_u = (u8_t)NULL;
//}
//
//bool
//u8_reserve(u8_t u, u8size_t reserve) {
//    if (u->length > reserve)
//        return false;
//    if (u->reserved >= reserve)
//        return true;
//    uint8ptr_t *new_bytes = (uint8ptr_t )realloc(u->bytes, sizeof(uint8ptr_t ) * reserve);
//    if (new_bytes==NULL)
//        return false;
//    u->bytes = new_bytes;
//    u->reserved = reserve;
//    if (u->reserved > u->length) {
//        u8size_t diff = u->reserved - u->length;
//        memset(u->bytes + u->length, 0, sizeof(uint8ptr_t) * diff);
//    }
//    return true;
//}
//
//bool
//u8_push(u8_t u, uint8ptr_t bytes) {
//    return u8_insert(u, item, u->length);
//}
//
//bool
//u8_insert(u8_t u, uint8ptr_t item, uint64_t pos) {
//    if (u->length < pos)
//        return false;
//    if (u->reserved == u->length) {
//        uint64_t reserve = u->length * 2;
//        if (!u8_reserve(u, reserve))
//            return false;
//    }
//    for (uint64_t i = u->length; i > pos; i--)
//        u->bytes[i] = u->bytes[i-1];
//
//    u->bytes[pos] = item;
//    u->length++;
//    return true;
//}


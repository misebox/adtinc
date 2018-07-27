#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "u8.h"


// utf-8 string
uint8_t u8_unit_size(uint8_t c) {
    if ((0x80 <= c && c <= 0xC1) || (0xF5 <= c)) {
        // Found an invalid byte
        return 0;
    }
    // Forward pointer to next character
    return ((c & 0x80) == 0)
         + ((c & 0xE0) == 0xC0) * 2
         + ((c & 0xF0) == 0xE0) * 3
         + ((c & 0xF8) == 0xF0) * 4;
}

u8size_t
u8_length(const char *s) {
    u8size_t length = 0;
    for(const char *max = s + u8_maxlength; *s != '\0'; length++) {
        uint8_t unit_size = u8_unit_size(*s & 0xFF);
        if ((uintptr_t)s >= (uintptr_t)max || unit_size == 0) {
            // Found an invalid byte or exceeded max length
            length = u8_none;
            break;
        }
        // Forward pointer to next character
        s += unit_size;
    }
    return length;
}

pu8
u8_new(const char* src) {
    pu8 u = (pu8)malloc(sizeof(struct _u8));
    if (u) {
        // get length
        u8size_t len = u8_length(src);
        if (len == u8_none) {
            goto failed;
        }
        u->length = len;
        // required byte size
        u8size_t str_size = strnlen(src, u->length * 4);
        u->size = str_size + 1; // for terminating character
        u->reserved = str_size * 2 + 1;

        // allocate memory
        u->bytes = (uint8ptr_t)malloc(u->reserved);
        if (!u->bytes)
            goto failed;
        // set data
        memcpy(u->bytes, src, u->reserved);
    }
    return u;

  failed:
    free(u);
    return NULL;
}

bool
u8_assign(pu8 u, const char*src) {
    if (u) {
        // get length
        u8size_t len = u8_length(src);
        if (len == u8_none) {
            return false;
        }
        // required byte size
        u8size_t str_size = strnlen(src, len * 4);
        u->size = str_size + 1; // for terminating character
        u8size_t size = str_size * 2 + 1;

        // allocate memory
        if (u->reserved < size)
            if (!u8_reserve(u, size))
                return false;
        u->length = len;
        // set data
        memcpy(u->bytes, src, u->reserved);
    }
    return false;
}

void
u8_free(pu8 *_u) {
    pu8 u = *_u;
    if (u) {
        free(u->bytes);
        u->bytes = NULL;
    }
    free(*_u);
    *_u = (pu8)NULL;
}

bool
u8_reserve(pu8 u, u8size_t reserve) {
    if (u->size > reserve)
        return false;
    if (u->reserved >= reserve)
        return true;
    uint8ptr_t new_bytes = (uint8ptr_t)realloc(u->bytes, reserve);
    if (!new_bytes)
        return false;
    u->bytes = new_bytes;
    u->reserved = reserve;
    if (u->reserved > u->size) {
        u8size_t diff = u->reserved - u->size;
        memset(u->bytes + u->size, 0, diff);
    }
    return true;
}

bool
u8_extend(pu8 dst, pu8 src) {
    u8size_t length = dst->length + src->length;
    if (u8_maxlength < length)
        return false;
    u8size_t size = dst->size + src->size - 1;
    if (dst->reserved < size) {
        if (!u8_reserve(dst, size))
            return false;
    }
    memcpy(dst->bytes + dst->size - 1, src->bytes, src->size);
    dst->size = size;
    dst->length = length;
    return true;
}

bool
u8_append(pu8 dst, char ch) {
    u8size_t length = dst->length + 1;
    if (u8_maxlength < length)
        return false;
    u8size_t size = dst->size + 1;
    if (dst->reserved < size) {
        if (!u8_reserve(dst, size))
            return false;
    }
    dst->bytes[dst->size - 1] = ch;
    dst->bytes[dst->size] = '\0';
    dst->size = size;
    dst->length = u8_length((const char *)dst->bytes);
    return true;
}

pu8
u8_slice(pu8 src, int32_t start_pos, int32_t end_pos) {
  pu8 dst = u8_new("");
  assert(u8_slice_into(dst, src, start_pos, end_pos));
  return dst;
}

bool
u8_slice_into(pu8 dst, pu8 src, int32_t start_pos, int32_t end_pos) {
    u8size_t start = start_pos >= 0 ? start_pos : src->length - abs(start_pos);
    u8size_t end = end_pos >= 0 ? end_pos : src->length - abs(end_pos);
    if (start_pos < 0 && end == 0)
        end = src->length;
    if (start > src->length || end > src->length || start > end)
        return false;
    uint8_t *p = src->bytes;
    uint8_t offset;
    uint8_t size;

    // inspecting bytes range
    if (start == end) {
        offset = 0;
        size = 1; // only terminating character
    } else {
        for (u8size_t pos = 0; pos < end; pos++) {
            uint8_t unit_size = u8_unit_size(*p);
            assert(unit_size);
            if (pos == start) {
                offset = (u8size_t)(p - src->bytes);
            }
            p += unit_size;
            if (pos >= end -1) {
                size = ((u8size_t)(p - src->bytes - offset)) + 1; // with a terminating character
                break;
            }
        }
    }
    if (dst->reserved < size) {
        if (!u8_reserve(dst, size))
            return false;
    }
    if (size > 1)
        memcpy(dst->bytes, src->bytes + offset, size -1);
    dst->bytes[size -1] = '\0';
    dst->size = size;
    dst->length = end - start;
    return true;
}

bool
u8_eq(pu8 lh, pu8 rh) {
    if (lh->size != rh->size || lh->length != rh->length)
        return false;
    u8size_t end = lh->size;
    for (u8size_t i = 0; i < end; i++)
        if (lh->bytes[i] != rh->bytes[i])
            return false;
    return true;
}

#include <stdlib.h>
#include <stdbool.h>


typedef uint32_t u8size_t;
typedef uint8_t *uint8ptr_t;
#define u8_none ((u8size_t)-1)
#define u8_maxlength (0xFFFF)

typedef struct _u8 u8_t;
typedef u8_t *pu8;
struct _u8 {
    // reserved size for bytes
    u8size_t reserved;
    // actual size of bytes
    u8size_t size;
    // length in UTF-8
    u8size_t length;
    // bytes array for UTF-8 string
    uint8ptr_t bytes;
};

#define u8_copy(dst, src) u8_slice(dst, src, 0, src->length);

/**
 * Count length for utf-8 string.
 * usage:
 *     u8size_t count = u8_length(u8"🍣🍣🍣"); // count == 3
 */
u8size_t
    u8_length(const char *str);

/**
 * Constructs a new pu8 object.
 * If failed to allocate required buffer, returns u8_none.
 * usage:
 *     pu8 u = u8_new(u8"🍣🍣🍣");
 *     if (!u) printf("failed");
 */
pu8
    u8_new(const char* src);

/**
 * Destruct pu8 object.
 * Requires a pointer of pu8 object as a argument.
 * Set NULL into pu8 object after freeing.
 * usage:
 *     pu8 u = u8_new(u8"🍣🍣🍣");
 *     u8_free(&u); // set NULL into
 *     u8_free(&u); // np
 */
void
u8_free(pu8 *_u);

/**
 * Reserve size of bytes in pu8 object.
 * Useful to avoid frequently reallocating for bytes.
 * Returns true if success else false.
 * usage:
 *     pu8 u = u8_new(u8"🍣🍣🍣");
 *     if (!u8_reserve(u, 30)) printf("failed\n");
 */
bool
    u8_reserve(pu8 u, u8size_t reserve);


/**
 * Concatenate two pu8 objects.
 * Second object is copied and connected to the tail of first object.
 * Allocate required size of memory if necessary.
 * Returns true if success else false.
 * usage:
 *     pu8 dst = u8_new(u8"🍣🍣🍣");
 *     pu8 src = u8_new(u8"🍺🍺🍺");
 *     bool ok = u8_extend(dst, src); // 🍣🍣🍣🍺🍺🍺
 */
bool
    u8_extend(pu8 dst, pu8 src);

/**
 * Copy substring of second object into first object.
 * Substring is from start_pos to end_pos in second object.
 * Reverse index like -5 (it means where length minus 5) is allowed.
 * usage:
 *     pu8 src = u8_new(u8"🍣🍣🍣🍺🍺🍺");
 *     pu8 dst = u8_new(u8"");
 *     if (u8_slice(dst, src, 2, 4)) printf("%s\n", dst->bytes); // 🍣🍺
 *     if (u8_slice(dst, src, 1, -1)) printf("%s\n", dst->bytes); // 🍣🍣🍺🍺
 */
bool
    u8_slice(pu8 dst, pu8 src, int32_t start_pos, int32_t end_pos);

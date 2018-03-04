#include <stdlib.h>
#include <stdbool.h>


#define DEBUG(msg) printf("File: %s, Func: %s, Line: %d, Msg: %s\n", __FILE__, __FUNCTION__, __LINE__, msg);
typedef uint32_t u8size_t;
typedef uint8_t *uint8ptr_t;
#define u8_none ((u8size_t)-1)
#define u8_maxlength (0xFFFF)

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
typedef struct _u8 *u8_t;


/**
 * Count length for utf-8 string.
 * usage:
 *     u8size_t count = u8_length(u8"🍣🍣🍣"); // count == 3
 */
u8size_t
    u8_length(const char *str);

/**
 * Constructs a new u8_t object.
 * If failed to allocate required buffer, returns u8_none.
 * usage:
 *     u8_t u = u8_new(u8"🍣🍣🍣");
 *     if (!u) printf("failed");
 */
u8_t
    u8_new(const char* src);

/**
 * Destruct u8_t object.
 * Requires a pointer of u8_t object as a argument.
 * Set NULL into u8_t object after freeing.
 * usage:
 *     u8_t u = u8_new(u8"🍣🍣🍣");
 *     u8_free(&u); // set NULL into
 *     u8_free(&u); // np
 */
void
u8_free(u8_t *_u);

/**
 * Reserve size of bytes in u8_t object.
 * Useful to avoid frequently reallocating for bytes.
 * Returns true if success else false.
 * usage:
 *     u8_t u = u8_new(u8"🍣🍣🍣");
 *     if (!u8_reserve(u, 30)) printf("failed\n");
 */
bool
    u8_reserve(u8_t u, u8size_t reserve);

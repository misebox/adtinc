#include <stdlib.h>
#include <stdbool.h>


#define DEBUG(msg) printf("File: %s, Func: %s, Line: %d, Msg: %s\n", __FILE__, __FUNCTION__, __LINE__, msg);
typedef uint32_t u8size_t;
typedef uint8_t *uint8ptr_t;
#define u8_none ((u8size_t)-1)
#define u8_maxlength (0xFFFF)

struct _u8 {
    u8size_t reserved;
    u8size_t length;
    uint8ptr_t bytes;
};
typedef struct _u8 *u8_t;

u8size_t
    u8_length(const char *str);

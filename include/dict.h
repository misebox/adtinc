#include <stdlib.h>
#include <stdbool.h>
#include "general.h"
#include "u8.h"


#define DEBUG(msg) printf("File: %s, Func: %s, Line: %d, Msg: %s\n", __FILE__, __FUNCTION__, __LINE__, msg);

typedef uint16_t dict_size_t;

struct _dict_item {
    pu8 key;
    voidptr_t value;
};
typedef struct _dict_item dict_item_t;
typedef dict_item_t *pdict_item;

struct _dict {
    pdict_item items;
    dict_size_t count;
    dict_size_t size;
};
typedef struct _dict dict_t;
typedef dict_t *pdict;


uint64_t
    dict_hash(pu8 key, dict_size_t size);

pdict
    dict_new(dict_size_t size);

void
    dict_free(pdict *pd);

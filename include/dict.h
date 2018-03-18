#include <stdlib.h>
#include <stdbool.h>
#include "general.h"
#include "u8.h"


#define dict_threshold (0.75)
#define dict_default_size (16)

typedef uint16_t dict_size_t;

struct _dict_item {
    dict_size_t hash;
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

/**
 * Calculate a hash from bytes in a pu8 object.
 * Requires a hash size as an argument.
 * Return value becomes between 0 and (size-1).
 */
dict_size_t
    dict_hash(pu8 key, dict_size_t size);

/**
 * Create a new pdict object.
 * Requires a size of hash map.
 * If failed to allocate, returns NULL.
 */
pdict
    dict_new(dict_size_t size);

/**
 * Free pdict object.
 * Requires a pointer of pdict object
 * Set NULL into pdict object after freeing.
 */
void
    dict_free(pdict *pd);

/**
 * Set an entry(key and value) into pdict.
 * Returns the stored address.
 */
dict_size_t
    dict_set(pdict d, pu8 k, voidptr_t v);

/**
 * Get a value by a key from pdict object.
 * Return a value pointer.
 */
voidptr_t
    dict_get(pdict d, pu8 k);

/**
 * The result is true if dict has key, false if not.
 */
bool
    dict_has_key(pdict d, pu8 k);


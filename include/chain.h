#include <stdlib.h>
#include <stdbool.h>
#include <general.h>

#define DEBUG(msg) printf("File: %s, Func: %s, Line: %d, Msg: %s\n", __FILE__, __FUNCTION__, __LINE__, msg);

typedef uint16_t chain_size_t;

typedef struct _chain_item chain_item_t;
typedef chain_item_t *pchain_item;
struct _chain_item {
    voidptr_t content;
    pchain_item next;
    pchain_item prev;
};

typedef struct _chain chain_t;
typedef chain_t *pchain;
struct _chain {
    pchain_item back;
    pchain_item front;
    chain_size_t size;
};



pchain
    chain_new(void);


void
    chain_free(pchain *_pc);


pchain_item
    chain_item_at(pchain pc, int32_t at);


bool
    chain_push_front(pchain pc, voidptr_t content);


bool
    chain_push_back(pchain pc, voidptr_t content);


voidptr_t
    chain_pop_front(pchain pc);


voidptr_t
    chain_pop_back(pchain pc);

#include <stdlib.h>
#include <stdbool.h>
#include <general.h>

#define DEBUG(msg) printf("File: %s, Func: %s, Line: %d, Msg: %s\n", __FILE__, __FUNCTION__, __LINE__, msg);

typedef struct _queue_item queue_item_t;
typedef queue_item_t *pqueue_item;
struct _queue_item {
    voidptr_t content;
    pqueue_item next;
    pqueue_item prev;
};

typedef struct _queue queue_t;
typedef queue_t *pqueue;
struct _queue {
    pqueue_item back;
    pqueue_item front;
    uint16_t size;
};


pqueue
    queue_new(void);


void
    queue_free(pqueue *_q);


bool
    queue_enqueue(pqueue q, voidptr_t content);


voidptr_t
    queue_dequeue(pqueue q);

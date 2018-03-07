#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"


pqueue
queue_new() {
    pqueue q = (pqueue)calloc(1, sizeof(queue_t));
    if (!q)
        return NULL;
    q->back = NULL;
    q->front = NULL;
    q->size = 0;
    return q;
}

void
queue_free(pqueue *_q) {
    pqueue q = *_q;
    pqueue_item prev = NULL;
    for (pqueue_item qi = q->front; qi != NULL; qi = prev) {
        prev = qi->prev;
        if (prev)
            prev->next = qi->next;
        free(qi);;
    }
    free(q);
    *_q = NULL;
}

pqueue_item
queue_item_new(voidptr_t content) {
    pqueue_item qi = (pqueue_item)calloc(1, sizeof(queue_item_t));
    if (!qi)
        return NULL;
    qi->next = NULL;
    qi->prev = NULL;
    qi->content = content;
    return qi;
}

bool
queue_enqueue(pqueue q, voidptr_t content) {
    pqueue_item qi = queue_item_new(content);
    if (!qi)
        return false;
    qi->prev = NULL;
    qi->next = q->back;
    if (q->back)
        q->back->prev = qi;
    q->back = qi;
    if (!q->front)
        q->front = qi;
    q->size ++;
    return true;
}

voidptr_t
queue_dequeue(pqueue q) {
    if (!q->front)
        return NULL;
    voidptr_t content = q->front->content;
    pqueue_item front = q->front->prev;
    if (front)
        front->next = NULL;
    free(q->front);
    if (q->front == q->back)
        q->back = NULL;
    q->front = front;
    q->size--;
    return content;
}

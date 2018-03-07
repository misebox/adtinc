#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "queue.h"

int main() {
    pqueue q = queue_new();
    assert(queue_enqueue(q, "Apple"));
    assert(queue_enqueue(q, "Banana"));
    assert(queue_enqueue(q, "Cherry"));
    assert(queue_enqueue(q, "Dates"));
    assert(queue_enqueue(q, "Elderberry"));
    printf("%u %p %p %s\n", q->size, q->back, q->front, (char *)queue_dequeue(q));
    printf("%u %p %p %s\n", q->size, q->back, q->front, (char *)queue_dequeue(q));
    printf("%u %p %p %s\n", q->size, q->back, q->front, (char *)queue_dequeue(q));
    printf("%u %p %p %s\n", q->size, q->back, q->front, (char *)queue_dequeue(q));
    printf("%u %p %p %s\n", q->size, q->back, q->front, (char *)queue_dequeue(q));
    printf("%u %p %p %s\n", q->size, q->back, q->front, (char *)queue_dequeue(q));
    printf("%u %p %p %s\n", q->size, q->back, q->front, (char *)queue_dequeue(q));
    queue_free(&q);
    return 0;
}

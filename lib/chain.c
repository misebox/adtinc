#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "chain.h"


pchain
chain_new() {
    pchain pc = (pchain)calloc(1, sizeof(chain_t));
    if (!pc)
        return NULL;
    pc->back = NULL;
    pc->front = NULL;
    pc->size = 0;
    return pc;
}

void
chain_free(pchain *_pc) {
    pchain pc = *_pc;
    pchain_item prev = NULL;
    for (pchain_item pci = pc->front; pci != NULL; pci = prev) {
        prev = pci->prev;
        if (prev)
            prev->next = pci->next;
        free(pci);;
    }
    free(pc);
    *_pc = NULL;
}

pchain_item
chain_item_at(pchain pc, int32_t at) {
    at = pc->size - abs(at);
    if (at >= pc->size)
        return NULL;
    pchain_item  p;
    if (at <= pc->size / 2) {
        // from back
        p = pc->back;
        for (chain_size_t i=0; i<at; i++) {
            assert(p->next);
            p = p->next;
        }
    } else {
        // from front
        p = pc->front;
        for (chain_size_t i = pc->size; i > 0; i--) {
            assert(p->prev);
            p = p->prev;
        }
    }
    return p;
}

pchain_item
chain_item_new(voidptr_t content) {
    pchain_item pci = (pchain_item)calloc(1, sizeof(chain_item_t));
    if (!pci)
        return NULL;
    pci->next = NULL;
    pci->prev = NULL;
    pci->content = content;
    return pci;
}

bool
chain_push_front(pchain pc, voidptr_t content) {
    pchain_item pci = chain_item_new(content);
    if (!pci)
        return false;
    pci->next = NULL;
    pci->prev = pc->front;
    if (pc->front)
        pc->front->next = pci;
    pc->front = pci;
    if (!pc->back)
        pc->back = pci;
    pc->size ++;
    return true;
}

bool
chain_push_back(pchain pc, voidptr_t content) {
    pchain_item pci = chain_item_new(content);
    if (!pci)
        return false;
    pci->prev = NULL;
    pci->next = pc->back;
    if (pc->back)
        pc->back->prev = pci;
    pc->back = pci;
    if (!pc->front)
        pc->front = pci;
    pc->size ++;
    return true;
}

voidptr_t
chain_pop_front(pchain pc) {
    if (!pc->front)
        return NULL;
    voidptr_t content = pc->front->content;
    pchain_item front = pc->front->prev;
    if (front)
        front->next = NULL;
    free(pc->front);
    if (pc->front == pc->back)
        pc->back = NULL;
    pc->front = front;
    pc->size--;
    return content;
}

voidptr_t
chain_pop_back(pchain pc) {
    if (!pc->back)
        return NULL;
    voidptr_t content = pc->back->content;
    pchain_item back = pc->back->next;
    if (back)
        back->prev = NULL;
    free(pc->back);
    if (pc->back == pc->front)
        pc->front = NULL;
    pc->back = back;
    pc->size--;
    return content;
}

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "chain.h"
static char *fruits[] = {
    "Apple",
    "Banana",
    "Cherry",
    "Dates",
    "Elderberry",
};

void
init_w_func(pchain pc, bool (*func)(pchain, voidptr_t)) {
    for (int i=0; i<5; i++) {
        assert(func(pc, (voidptr_t)fruits[i]) == true);
    }
}

void
print_w_func(pchain pc, voidptr_t (*func)(pchain)) {
    for (int i=0; i<6; i++) {
        printf("%u %p %p %s\n", pc->size, pc->back, pc->front, (char *)func(pc));
    }
}


int main() {
    pchain pc = chain_new();

    printf("push_back and pop_front\n");
    init_w_func(pc, chain_push_back);
    print_w_func(pc, chain_pop_front);

    printf("push_back and pop_back\n");
    init_w_func(pc, chain_push_back);
    print_w_func(pc, chain_pop_back);

    printf("push_front and pop_front\n");
    init_w_func(pc, chain_push_front);
    print_w_func(pc, chain_pop_front);

    printf("push_front and pop_back\n");
    init_w_func(pc, chain_push_front);
    print_w_func(pc, chain_pop_back);

    chain_free(&pc);
    return 0;
}

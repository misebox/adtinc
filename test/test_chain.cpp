#include "gtest/gtest.h"
extern "C" {
#include "chain.h"
#include <cstddef>
}


class chain: public ::testing::Test {
protected:
    const char *apple = "Apple";
    const char *banana = "Banana";
    const char *cherry = "Cherry";
    const char *fruits[3] = {
        apple,
        banana,
        cherry,
    };

    void
    init_w_func(pchain pc, bool (*func)(pchain, voidptr_t)) {
        for (int i=0; i<3; i++) {
            assert(func(pc, (voidptr_t)fruits[i]));
        }
    }

    void
    print_w_func(pchain pc, voidptr_t (*func)(pchain)) {
        for (int i=0; i<6; i++) {
            printf("%u %p %p %s\n", pc->size, pc->back, pc->front, (const char *)func(pc));
        }
    }
};


TEST_F(chain, test_chain_new_and_free)
{
    pchain pc = chain_new();
    ASSERT_NE((pchain) NULL, pc);
    EXPECT_EQ(0, pc->size);
    EXPECT_EQ((pchain_item)NULL, pc->front);
    EXPECT_EQ((pchain_item)NULL, pc->back);
    chain_free(&pc);
    ASSERT_EQ((pchain) NULL, pc);
}

TEST_F(chain, test_chain_item_new_and_free)
{
    pchain pc = chain_new();
    chain_free(&pc);
    ASSERT_EQ((pchain) NULL, pc);
}

TEST_F(chain, test_push_front)
{
    chain_t pc = {0};
    EXPECT_EQ(0, pc.size);
    EXPECT_EQ(pc.front, (pchain_item)NULL);
    EXPECT_EQ(pc.back, (pchain_item)NULL);
    init_w_func(&pc, chain_push_front);
    EXPECT_EQ(3, pc.size);
    EXPECT_EQ(pc.front->next, (pchain_item)NULL);
    EXPECT_EQ(pc.back->prev, (pchain_item)NULL);
    EXPECT_EQ(pc.front->content, cherry);
    EXPECT_EQ(pc.front->prev->content, banana);
    EXPECT_EQ(pc.front->prev->prev->content, apple);
    EXPECT_EQ(pc.front->prev->prev->prev, (pchain_item)NULL);
    EXPECT_EQ(pc.back->content, apple);
    EXPECT_EQ(pc.back->next->content, banana);
    EXPECT_EQ(pc.back->next->next->content, cherry);
    EXPECT_EQ(pc.back->next->next->next, (pchain_item)NULL);
}

TEST_F(chain, test_push_back)
{
    chain_t pc = {0};
    EXPECT_EQ(0, pc.size);
    EXPECT_EQ(pc.front, (pchain_item)NULL);
    EXPECT_EQ(pc.back, (pchain_item)NULL);
    init_w_func(&pc, chain_push_back);
    EXPECT_EQ(3, pc.size);
    EXPECT_EQ(pc.front->next, (pchain_item)NULL);
    EXPECT_EQ(pc.back->prev, (pchain_item)NULL);
    EXPECT_EQ(pc.front->content, apple);
    EXPECT_EQ(pc.front->prev->content, banana);
    EXPECT_EQ(pc.front->prev->prev->content, cherry);
    EXPECT_EQ(pc.front->prev->prev->prev, (pchain_item)NULL);
    EXPECT_EQ(pc.back->content, cherry);
    EXPECT_EQ(pc.back->next->content, banana);
    EXPECT_EQ(pc.back->next->next->content, apple);
    EXPECT_EQ(pc.back->next->next->next, (pchain_item)NULL);
}

TEST_F(chain, test_pop_front_after_push_back)
{
    chain_t pc = {0};
    init_w_func(&pc, chain_push_back);
    EXPECT_EQ(3, pc.size);
    EXPECT_EQ(chain_pop_front(&pc), apple);
    EXPECT_EQ(2, pc.size);
    EXPECT_EQ(pc.front->next, (pchain_item)NULL);
    EXPECT_EQ(pc.front->content, banana);
    EXPECT_EQ(pc.front->prev->content, cherry);
    EXPECT_EQ(pc.front->prev, pc.back);
    EXPECT_EQ(pc.back->prev, (pchain_item)NULL);
    EXPECT_EQ(chain_pop_front(&pc), banana);
    EXPECT_EQ(1, pc.size);
    EXPECT_EQ(pc.front->next, (pchain_item)NULL);
    EXPECT_EQ(pc.front->content, cherry);
    EXPECT_EQ(pc.front, pc.back);
    EXPECT_EQ(pc.front->prev, (pchain_item)NULL);
    EXPECT_EQ(chain_pop_front(&pc), cherry);
    EXPECT_EQ(0, pc.size);
    EXPECT_EQ(pc.front, (pchain_item)NULL);
    EXPECT_EQ(pc.front, pc.back);
    EXPECT_EQ(chain_pop_front(&pc), (pchain_item)NULL);
    EXPECT_EQ(0, pc.size);
}

TEST_F(chain, test_pop_back_after_push_back)
{
    chain_t pc = {0};
    init_w_func(&pc, chain_push_back);
    EXPECT_EQ(3, pc.size);
    EXPECT_EQ(chain_pop_back(&pc), cherry);
    EXPECT_EQ(2, pc.size);
    EXPECT_EQ(pc.front->next, (pchain_item)NULL);
    EXPECT_EQ(pc.front->content, apple);
    EXPECT_EQ(pc.front->prev->content, banana);
    EXPECT_EQ(pc.front->prev, pc.back);
    EXPECT_EQ(pc.back->prev, (pchain_item)NULL);
    EXPECT_EQ(chain_pop_back(&pc), banana);
    EXPECT_EQ(1, pc.size);
    EXPECT_EQ(pc.front->next, (pchain_item)NULL);
    EXPECT_EQ(pc.front->content, apple);
    EXPECT_EQ(pc.front, pc.back);
    EXPECT_EQ(pc.front->prev, (pchain_item)NULL);
    EXPECT_EQ(chain_pop_back(&pc), apple);
    EXPECT_EQ(0, pc.size);
    EXPECT_EQ(pc.front, (pchain_item)NULL);
    EXPECT_EQ(pc.front, pc.back);
    EXPECT_EQ(chain_pop_back(&pc), (pchain_item)NULL);
    EXPECT_EQ(0, pc.size);
}

TEST_F(chain, test_pop_front_after_push_front)
{
    chain_t pc = {0};
    init_w_func(&pc, chain_push_front);
    EXPECT_EQ(3, pc.size);
    EXPECT_EQ(chain_pop_front(&pc), cherry);
    EXPECT_EQ(2, pc.size);
    EXPECT_EQ(pc.front->next, (pchain_item)NULL);
    EXPECT_EQ(pc.front->content, banana);
    EXPECT_EQ(pc.front->prev->content, apple);
    EXPECT_EQ(pc.front->prev, pc.back);
    EXPECT_EQ(pc.back->prev, (pchain_item)NULL);
    EXPECT_EQ(chain_pop_front(&pc), banana);
    EXPECT_EQ(1, pc.size);
    EXPECT_EQ(pc.front->next, (pchain_item)NULL);
    EXPECT_EQ(pc.front->content, apple);
    EXPECT_EQ(pc.front, pc.back);
    EXPECT_EQ(pc.front->prev, (pchain_item)NULL);
    EXPECT_EQ(chain_pop_front(&pc), apple);
    EXPECT_EQ(0, pc.size);
    EXPECT_EQ(pc.front, (pchain_item)NULL);
    EXPECT_EQ(pc.front, pc.back);
    EXPECT_EQ(chain_pop_front(&pc), (pchain_item)NULL);
    EXPECT_EQ(0, pc.size);
}

TEST_F(chain, test_pop_back_after_push_front)
{
    chain_t pc = {0};
    init_w_func(&pc, chain_push_front);
    EXPECT_EQ(3, pc.size);
    EXPECT_EQ(chain_pop_back(&pc), apple);
    EXPECT_EQ(2, pc.size);
    EXPECT_EQ(pc.front->next, (pchain_item)NULL);
    EXPECT_EQ(pc.front->content, cherry);
    EXPECT_EQ(pc.front->prev->content, banana);
    EXPECT_EQ(pc.front->prev, pc.back);
    EXPECT_EQ(pc.back->prev, (pchain_item)NULL);
    EXPECT_EQ(chain_pop_back(&pc), banana);
    EXPECT_EQ(1, pc.size);
    EXPECT_EQ(pc.front->next, (pchain_item)NULL);
    EXPECT_EQ(pc.front->content, cherry);
    EXPECT_EQ(pc.front, pc.back);
    EXPECT_EQ(pc.front->prev, (pchain_item)NULL);
    EXPECT_EQ(chain_pop_back(&pc), cherry);
    EXPECT_EQ(0, pc.size);
    EXPECT_EQ(pc.front, (pchain_item)NULL);
    EXPECT_EQ(pc.front, pc.back);
    EXPECT_EQ(chain_pop_back(&pc), (pchain_item)NULL);
    EXPECT_EQ(0, pc.size);
}

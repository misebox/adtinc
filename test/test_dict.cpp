#include "gtest/gtest.h"
extern "C" {
#include "dict.h"
#include <cstddef>
}


class dict: public ::testing::Test {
protected:
    const char *apple = "Apple";
    const char *banana = "Banana";
    const char *cherry = "Cherry";
    const char *fruits[3] = {
        apple,
        banana,
        cherry,
    };
};

TEST_F(dict, test_dict_new_and_free)
{
    pdict pd = dict_new(100);
    ASSERT_NE((pdict) NULL, pd);
    EXPECT_EQ(100, pd->size);
    EXPECT_EQ(0, pd->count);
    EXPECT_NE((pdict_item)NULL, pd->items);
    dict_free(&pd);
    ASSERT_EQ((pdict) NULL, pd);
}

TEST_F(dict, test_dict_item_new_and_free)
{
    pdict pd = dict_new(100);
    dict_free(&pd);
    ASSERT_EQ((pdict) NULL, pd);
}


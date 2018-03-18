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

TEST_F(dict, test_dict_set)
{
    pdict pd = dict_new(100);
    pu8 key = u8_new("This is a key.");
    dict_size_t addr = dict_set(pd, key, (voidptr_t)apple);
    pdict_item item = pd->items + addr;
    EXPECT_EQ(100, pd->size);
    EXPECT_EQ(1, pd->count);
    EXPECT_EQ(item->hash, addr);
    EXPECT_EQ(item->key, key);
    EXPECT_EQ(item->value, apple);
    u8_free(&key);
    dict_free(&pd);
}

TEST_F(dict, test_dict_get)
{
    pdict pd = dict_new(100);
    pu8 key1 = u8_new("This is a key.");
    pu8 key2 = u8_new("This is a key.2222");
    //dict_size_t addr;
    //const char *val;
    //addr = dict_set(pd, key1, (voidptr_t)apple);
    //val = (const char *)dict_get(pd, key1);
    //EXPECT_EQ(val, apple);
    //addr = dict_set(pd, key2, (voidptr_t)banana);
    //val = (const char *)dict_get(pd, key2);
    //EXPECT_EQ(val, banana);
    u8_free(&key1);
    u8_free(&key2);
    dict_free(&pd);
}

#include "gtest/gtest.h"
extern "C" {
#include "vec.h"
#include <cstddef>
}

class fixtureName : public ::testing::Test {
protected:
    virtual void SetUp(){
    }
    virtual void TearDown(){
    }
};

TEST_F(fixtureName, test_vec_new_and_free)
{
    vec_t v = vec_new();
    ASSERT_NE((vec_t) NULL, v);
    EXPECT_EQ(0, v->length);
    EXPECT_EQ(8, v->reserved);
    vec_free(&v);
    EXPECT_EQ((vec_t) NULL, v);
}

TEST_F(fixtureName, test_vec_add)
{
    vec_t v = vec_new();
    ASSERT_NE((vec_t) NULL, v);
    int64_t a = 1, b = 2, c = 3;
    EXPECT_TRUE(vec_add(v, &a));
    EXPECT_TRUE(vec_add(v, &b));
    EXPECT_TRUE(vec_add(v, &c));
    EXPECT_EQ(&a, vec_get(v, 0));
    EXPECT_EQ(&b, vec_get(v, 1));
    EXPECT_EQ(&c, vec_get(v, 2));
    EXPECT_EQ(3, v->length);
    EXPECT_EQ(8, v->reserved);
    vec_free(&v);
    EXPECT_EQ((vec_t) NULL, v);
}

TEST_F(fixtureName, test_reserving_correctly)
{
    int64_t reserved = 8;
    vec_t v = vec_new();
    ASSERT_NE((vec_t) NULL, v);
    int64_t a[9] = {99};
    EXPECT_EQ(8, v->reserved);
    for (int64_t i = 0; i < reserved + 1; i++) {
        EXPECT_TRUE(vec_add(v, &a[i]));
        EXPECT_EQ(&a[i], vec_get(v, i));
    }

    EXPECT_EQ(reserved + 1, v->length);
    EXPECT_EQ(reserved * 2, v->reserved);
    vec_free(&v);
    EXPECT_EQ((vec_t) NULL, v);
}

TEST_F(fixtureName, test_vec_add_many_items)
{
    vec_t v = vec_new();
    ASSERT_NE((vec_t) NULL, v);
    int64_t a = 99;
    int64_t res = 8;
    for (int64_t i = 0; i < 0x10000; i++) {
        EXPECT_TRUE(vec_add(v, &a));
        EXPECT_EQ(&a, vec_get(v, i));
        if (res < i) {
            res *= 2;
            EXPECT_EQ(res, v->reserved);
        }
    }

    EXPECT_EQ(0x10000, v->length);
    vec_free(&v);
    EXPECT_EQ((vec_t) NULL, v);
}

TEST_F(fixtureName, test_vec_reserve)
{
    vec_t v = vec_new();
    ASSERT_NE((vec_t) NULL, v);
    int64_t a = 99;
    int64_t res = 0x10000;
    EXPECT_TRUE(vec_add(v, &a));
    EXPECT_EQ(&a, vec_get(v, 0));
    EXPECT_TRUE(vec_reserve(v, res));
    EXPECT_EQ(res, v->reserved);

    EXPECT_EQ(1, v->length);
    EXPECT_EQ(a, 99);
    EXPECT_EQ(&a, vec_get(v, 0));
    vec_free(&v);
    EXPECT_EQ((vec_t) NULL, v);
}

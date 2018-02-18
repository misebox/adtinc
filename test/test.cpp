#include "gtest/gtest.h"
extern "C" {
#include "vec.h"
#include <cstddef>
}

class fixture_none: public ::testing::Test {
};

class for_vec: public ::testing::Test {
protected:
    vec_t f_empty_;
    vec_t f_three_;
    int64_t f_a_, f_b_, f_c_;

    virtual void SetUp(){
        f_empty_ = vec_new();
        f_a_ = 10, f_b_ = 20, f_c_ = 30;
        f_three_ = vec_new();
        vec_push(f_three_, &f_a_);
        vec_push(f_three_, &f_b_);
        vec_push(f_three_, &f_c_);
    }
    virtual void TearDown(){
        vec_free(&f_empty_);
        vec_free(&f_three_);
    }
};

TEST_F(fixture_none, test_vec_new_and_free)
{
    vec_t v = vec_new();
    ASSERT_NE((vec_t) NULL, v);
    EXPECT_EQ(0, v->length);
    EXPECT_EQ(8, v->reserved);
    vec_free(&v);
    ASSERT_EQ((vec_t) NULL, v);
}

TEST_F(fixture_none, test_vec_push_and_get)
{
    vec_t v = vec_new();
    int64_t f_a_ = 1, f_b_ = 2, f_c_ = 3;
    EXPECT_TRUE(vec_push(v, &f_a_));
    EXPECT_TRUE(vec_push(v, &f_b_));
    EXPECT_TRUE(vec_push(v, &f_c_));
    EXPECT_EQ(&f_a_, vec_get(v, 0));
    EXPECT_EQ(&f_b_, vec_get(v, 1));
    EXPECT_EQ(&f_c_, vec_get(v, 2));
    EXPECT_EQ(NULL, vec_get(v, 3));
    EXPECT_EQ(3, v->length);
    EXPECT_EQ(8, v->reserved);
    vec_free(&v);
}

TEST_F(for_vec, test_vec_insert)
{
    vec_t v = f_empty_;
    int64_t f_a_ = 1, f_b_ = 2, f_c_ = 3, d = 4;
    EXPECT_TRUE(vec_insert(v, &f_a_, 0));
    EXPECT_TRUE(vec_insert(v, &f_c_, 1));
    EXPECT_TRUE(vec_insert(v, &f_b_, 1));
    EXPECT_FALSE(vec_insert(v, &d, 4));
    EXPECT_EQ(&f_a_, v->items[0]);
    EXPECT_EQ(&f_b_, v->items[1]);
    EXPECT_EQ(&f_c_, v->items[2]);
    EXPECT_EQ(3, v->length);
    EXPECT_EQ(8, v->reserved);
}

TEST_F(for_vec, test_vec_del)
{
    vec_t v = f_three_;
    EXPECT_EQ(3, v->length);
    EXPECT_FALSE(vec_del(v, 3));
    EXPECT_EQ(3, v->length);
    EXPECT_TRUE(vec_del(v, 1));
    EXPECT_EQ(2, v->length);
    EXPECT_TRUE(vec_del(v, 1));
    EXPECT_EQ(1, v->length);
    EXPECT_FALSE(vec_del(v, 1));
    EXPECT_TRUE(vec_del(v, 0));
    EXPECT_EQ(0, v->length);
    EXPECT_FALSE(vec_del(v, 0));
}

TEST_F(for_vec, test_vec_pop)
{
    vec_t v = f_three_;
    EXPECT_EQ(&f_c_, vec_pop(v));
    EXPECT_EQ(2, v->length);
    EXPECT_EQ(&f_b_, vec_pop(v));
    EXPECT_EQ(1, v->length);
    EXPECT_EQ(&f_a_, vec_pop(v));
    EXPECT_EQ(0, v->length);
    EXPECT_EQ(NULL, vec_pop(v));
}

TEST_F(for_vec, test_vec_push_many_items)
{
    vec_t v = f_empty_;
    int64_t f_a_ = 99;
    int64_t res = v->reserved;
    for (int64_t i = 0; i < 0x10000; i++) {
        EXPECT_TRUE(vec_push(v, &f_a_));
        EXPECT_EQ(&f_a_, vec_get(v, i));
        EXPECT_EQ(v->length, i+1);
        if (res < i) {
            res *= 2;
            EXPECT_EQ(res, v->reserved);
        }
    }
}

TEST_F(for_vec, test_vec_reserve)
{
    vec_t v = f_three_;
    uint64_t length = v->length;
    // No changes when enough already
    uint64_t res = v->reserved;
    EXPECT_TRUE(vec_reserve(v, v->reserved - 1));
    EXPECT_EQ(res, v->reserved);
    // 256K bytes
    EXPECT_TRUE(vec_reserve(v, 0x10000));
    EXPECT_EQ(0x10000, v->reserved);
    EXPECT_EQ(length, v->length);
    EXPECT_EQ(&f_a_, v->items[0]);
    EXPECT_EQ(&f_b_, v->items[1]);
    EXPECT_EQ(&f_c_, v->items[2]);
    // less than length
    EXPECT_FALSE(vec_reserve(v, 2));
}

TEST_F(for_vec, test_vec_copy)
{
    vec_t v = f_three_;
    vec_t v_dst = vec_copy(v);
    EXPECT_NE(v, v_dst);
    EXPECT_NE(v->items, v_dst->items);
    EXPECT_NE((vec_t) NULL, v_dst);
    EXPECT_EQ(&f_a_, vec_get(v_dst, 0));
    EXPECT_EQ(&f_b_, vec_get(v_dst, 1));
    EXPECT_EQ(&f_c_, vec_get(v_dst, 2));
    EXPECT_EQ(v->length, v_dst->length);
    EXPECT_EQ(v->reserved, v_dst->reserved);
    vec_free(&v_dst);
    EXPECT_EQ((vec_t) NULL, v_dst);
}

TEST_F(for_vec, test_vec_copy_slice)
{
    vec_t v = f_three_;
    vec_t v_dst;
    v_dst = vec_copy_slice(v, 3, 4);
    EXPECT_EQ(NULL, vec_copy_slice(v, 3, 4));
    v_dst = vec_copy_slice(v, 1, 2);
    EXPECT_NE(v, v_dst);
    EXPECT_NE((vec_t) NULL, v_dst);
    EXPECT_EQ(&f_b_, vec_get(v_dst, 0));
    EXPECT_EQ(1, v_dst->length);
    EXPECT_EQ(8, v_dst->reserved);
    vec_free(&v_dst);
    v_dst = vec_copy_slice(v, 1, 1);
    EXPECT_NE((vec_t) NULL, v_dst);
    EXPECT_EQ(0, v_dst->length);
    vec_free(&v_dst);
}

TEST_F(for_vec, test_vec_copy_slice_returns_false)
{
    vec_t v = f_empty_;
    uint64_t res = v->reserved;
    for (uint64_t i=0; i<res+1; i++)
        vec_push(v, &f_a_);
    vec_t v_dst = vec_copy_slice(v, 0, res+1);
    EXPECT_NE((vec_t) NULL, v_dst);
    EXPECT_EQ(res+1, v_dst->length);
    EXPECT_LT(res, v_dst->reserved);
    vec_free(&v_dst);
}

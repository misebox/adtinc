#include "gtest/gtest.h"
extern "C" {
#include "u8.h"
#include <cstddef>
}
#include <tuple>

class fixture_none: public ::testing::Test {
};

class for_u8: public ::testing::Test {
protected:
    const char *f_zerochar_ = u8"";
    const char *f_1bytes_ = u8"a";
    const char *f_2bytes_ = u8"α";
    const char *f_3bytes_ = u8"あ";
    const char *f_4bytes_ = u8"🍣";
    const char *f_1bytes_x3_ = u8"abc";
    const char *f_2bytes_x3_ = u8"αβγ";
    const char *f_3bytes_x3_ = u8"あいう";
    const char *f_4bytes_x3_ = u8"🍣🍺🍀";
    const char *f_mixed_12_ = u8"abcαβγあいう🍣🍺🍀";
    char *f_maxlength_;
    char *f_overlength_;
    // expects <utf-8 string, length, bytes>
    std::tuple<const char *, u8size_t, u8size_t> f_expects_[10];
    u8size_t f_expects_size_ = 10;

    virtual void SetUp(){
        f_maxlength_ = (char*)malloc(u8_maxlength + 1);
        memset(f_maxlength_, 'X', u8_maxlength);
        f_maxlength_[u8_maxlength] = '\0';
        f_overlength_ = (char*)malloc(u8_maxlength+2);
        memset(f_overlength_, 'X', u8_maxlength + 1);
        f_overlength_[u8_maxlength+1] = '\0';
        f_expects_[0] = std::make_tuple(f_zerochar_, 0, 1);
        f_expects_[1] = std::make_tuple(f_1bytes_, 1, 2);
        f_expects_[2] = std::make_tuple(f_2bytes_, 1, 3);
        f_expects_[3] = std::make_tuple(f_3bytes_, 1, 4);
        f_expects_[4] = std::make_tuple(f_4bytes_, 1, 5);
        f_expects_[5] = std::make_tuple(f_1bytes_x3_, 3, 4);
        f_expects_[6] = std::make_tuple(f_2bytes_x3_, 3, 7);
        f_expects_[7] = std::make_tuple(f_3bytes_x3_, 3, 10);
        f_expects_[8] = std::make_tuple(f_4bytes_x3_, 3, 13);
        f_expects_[9] = std::make_tuple(f_mixed_12_, 12, 31);
    }
    virtual void TearDown(){
        free(f_maxlength_);
        f_maxlength_ = NULL;
        free(f_overlength_);
        f_overlength_ = NULL;
    }
};

TEST_F(for_u8, test_u8_length)
{
    for (int i=0; i<f_expects_size_; i++) {
        const char *src = std::get<0>(f_expects_[i]);
        u8size_t size = std::get<1>(f_expects_[i]);
        EXPECT_EQ(size, u8_length(src));
    }
    EXPECT_EQ(u8_maxlength, u8_length(f_maxlength_));
    EXPECT_EQ(u8_none, u8_length(f_overlength_));
    char invalid[2] = {0, 0};
    for (uint16_t i = 0x80; i <= 0xC1; i++) {
        invalid[0] = i;
        EXPECT_EQ(u8_none, u8_length(invalid));
    }
    for (uint16_t i = 0xF5; i <= 0xFF; i++) {
        invalid[0] = i;
        EXPECT_EQ(u8_none, u8_length(invalid));
    }
}

TEST_F(for_u8, test_u8_new_and_free)
{
    for (int i=0; i<f_expects_size_; i++) {
        const char *src = std::get<0>(f_expects_[i]);
        pu8 u = u8_new(src);
        ASSERT_NE((pu8) NULL, u);
        EXPECT_EQ(u->length, std::get<1>(f_expects_[i]));
        EXPECT_EQ(u->size, std::get<2>(f_expects_[i]));
        EXPECT_EQ(u->reserved, std::get<2>(f_expects_[i]) * 2 -1);
        EXPECT_STREQ((const char *)u->bytes, src);
        u8_free(&u);
        EXPECT_EQ((pu8) NULL, u);
    }
    pu8 u = u8_new(f_maxlength_);
    ASSERT_NE((pu8) NULL, u);
    EXPECT_EQ(u->length, u8_maxlength);
    EXPECT_EQ(u->reserved, u8_maxlength * 2 + 1);
    EXPECT_STREQ((const char *)u->bytes, f_maxlength_);
    u8_free(&u);
    ASSERT_EQ((pu8) NULL, u);
}

TEST_F(for_u8, test_u8_reserve)
{
    pu8 u;
    u = u8_new(f_2bytes_x3_);
    EXPECT_EQ(u->reserved, 13);
    EXPECT_FALSE(u8_reserve(u, 6));
    EXPECT_TRUE(u8_reserve(u, 7));
    EXPECT_EQ(u->reserved, 13);
    EXPECT_TRUE(u8_reserve(u, 100));
    EXPECT_EQ(u->reserved, 100);
    EXPECT_STREQ((const char *)u->bytes, f_2bytes_x3_);
    u8_free(&u);
    ASSERT_EQ((pu8) NULL, u);
}

TEST_F(for_u8, test_u8_extend)
{
    for (uint8_t si=0; si<f_expects_size_; si++) {
        pu8 src = u8_new((const char *)std::get<0>(f_expects_[si]));
        ASSERT_NE((pu8) NULL, src);
        for (uint8_t di=0; di<f_expects_size_; di++) {
            pu8 dst = u8_new((const char *)std::get<0>(f_expects_[di]));
            ASSERT_NE((pu8) NULL, dst);
            u8size_t length = std::get<1>(f_expects_[di]) + std::get<1>(f_expects_[si]);
            u8size_t size = std::get<2>(f_expects_[di]) + std::get<2>(f_expects_[si]) -1;
            char *expect = (char *)malloc(size);
            memcpy(expect, dst->bytes, dst->size - 1);
            memcpy(expect + dst->size - 1, src->bytes, src->size);
            ASSERT_TRUE(u8_extend(dst, src));
            EXPECT_STREQ((const char *)expect, (const char *)dst->bytes);
            ASSERT_EQ(dst->length, length);
            ASSERT_EQ(dst->size, size);
            ASSERT_TRUE(dst->reserved >= size);
            u8_free(&dst);
            ASSERT_EQ((pu8) NULL, dst);
        }
        u8_free(&src);
        ASSERT_EQ((pu8) NULL, src);
    }
}

TEST_F(for_u8, test_u8_slice)
{
    pu8 src;
    pu8 dst = u8_new(u8"");
    // f_expects_[5..8] starts with f_expects_[1..4]
    for (uint8_t si = 1; si <= 4; si++) {
        uint8_t li = si + 4; //5..8
        src = u8_new(std::get<0>(f_expects_[li]));
        ASSERT_TRUE(u8_slice(dst, src, 0, 1));
        EXPECT_EQ(dst->length, 1);
        EXPECT_STREQ((const char *)std::get<0>(f_expects_[si]), (const char *)dst->bytes);
        u8_free(&src);
    }

    // zero length string
    src = u8_new("abc");
    ASSERT_TRUE(u8_slice(dst, src, 0, 0));
    EXPECT_EQ(dst->length, 0);
    EXPECT_STREQ("", (const char *)dst->bytes);
    u8_free(&src);

    // zero length string
    src = u8_new("abc");
    ASSERT_TRUE(u8_slice(dst, src, 3, 3));
    EXPECT_EQ(dst->length, 0);
    EXPECT_STREQ("", (const char *)dst->bytes);
    u8_free(&src);

    // minus to zero specified
    src = u8_new("abc");
    ASSERT_TRUE(u8_slice(dst, src, -3, 0));
    EXPECT_EQ(dst->length, 3);
    EXPECT_STREQ("abc", (const char *)dst->bytes);
    u8_free(&src);
    u8_free(&dst);
}

TEST_F(for_u8, test_u8_slice_failed)
{
    // pu8 src = u8_new(u8"abcdef");
    // pu8 dst = u8_new(u8"");
    // EXPECT_FALSE(u8_slice(dst, src, 6, 6));
    // u8_free(&src);
    // u8_free(&dst);
}


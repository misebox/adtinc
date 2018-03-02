#include "gtest/gtest.h"
extern "C" {
#include "u8.h"
#include <cstddef>
}

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

    virtual void SetUp(){
        f_maxlength_ = (char*)malloc(u8_maxlength);
        memset(f_maxlength_, 'X', u8_maxlength);
        f_overlength_ = (char*)malloc(u8_maxlength+1);
        memset(f_overlength_, 'X', u8_maxlength+1);
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
    EXPECT_EQ(0, u8_length(f_zerochar_));
    EXPECT_EQ(1, u8_length(f_1bytes_));
    EXPECT_EQ(1, u8_length(f_2bytes_));
    EXPECT_EQ(1, u8_length(f_3bytes_));
    EXPECT_EQ(1, u8_length(f_4bytes_));
    EXPECT_EQ(3, u8_length(f_1bytes_x3_));
    EXPECT_EQ(3, u8_length(f_2bytes_x3_));
    EXPECT_EQ(3, u8_length(f_3bytes_x3_));
    EXPECT_EQ(3, u8_length(f_4bytes_x3_));
    EXPECT_EQ(12, u8_length(f_mixed_12_));
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

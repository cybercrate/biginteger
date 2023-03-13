#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_checking, is_negative_1) {
    EXPECT_TRUE(alf::num::big_integer{-512}.is_negative());
}

TEST(alef_numerics_biginteger_checking, is_negative_2) {
    EXPECT_FALSE(alf::num::big_integer{256}.is_negative());
}

TEST(alef_numerics_biginteger_checking, is_negative_zero) {
    EXPECT_FALSE(alf::num::big_integer{0}.is_negative());
}

#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_checking, is_negative_1) {
    EXPECT_TRUE(big_integer{-512}.is_negative());
}

TEST(biginteger_checking, is_negative_2) {
    EXPECT_FALSE(big_integer{256}.is_negative());
}

TEST(biginteger_checking, is_negative_zero) {
    EXPECT_FALSE(big_integer{0}.is_negative());
}

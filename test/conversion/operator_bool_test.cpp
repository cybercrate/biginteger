#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_conversion, operator_bool_positive) {
    EXPECT_TRUE(big_integer{120'000});
}

TEST(biginteger_conversion, operator_bool_negative) {
    EXPECT_TRUE(big_integer{-120'000});
}

TEST(biginteger_conversion, operator_bool_zero) {
    EXPECT_FALSE(big_integer{0});
}

#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_math, negate_positive) {
    EXPECT_EQ(-1782737, big_integer{1782737}.negate());
}

TEST(biginteger_math, negate_negative) {
    EXPECT_EQ(327327389182, big_integer{-327327389182}.negate());
}

TEST(biginteger_math, negate_zero) {
    EXPECT_EQ(0, big_integer{}.negate());
}

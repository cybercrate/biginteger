#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_math, abs_positive_1)
{
    EXPECT_EQ(1782737, big_integer{1782737}.abs());
}

TEST(biginteger_math, abs_negative_1)
{
    EXPECT_EQ(327327389182, big_integer{-327327389182}.abs());
}

TEST(biginteger_math, abs_zero_1)
{
    EXPECT_EQ(0, big_integer{}.abs());
}

#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_math, pow10_1)
{
    EXPECT_EQ(big_integer{16}.pow10(), "10000000000000000");
}

TEST(biginteger_math, pow10_2)
{
    EXPECT_EQ(
        big_integer{64}.pow10(),
        "10000000000000000000000000000000000000000000000000000000000000000");
}

#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_comparison, less_1)
{
    EXPECT_TRUE(big_integer{128} < big_integer{256});
}

TEST(biginteger_comparison, less_2)
{
    EXPECT_TRUE(big_integer{-128} < big_integer{256});
}

TEST(biginteger_comparison, less_3)
{
    EXPECT_TRUE(big_integer{-128} < big_integer{-64});
}

TEST(biginteger_comparison, less_4)
{
    EXPECT_FALSE(big_integer{0} < big_integer{0});
}

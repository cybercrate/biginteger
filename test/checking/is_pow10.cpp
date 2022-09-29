#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_checking, is_pow10_1)
{
    big_integer number{"10000000000000000000000000000000000000000000000000000000000000000"};
    EXPECT_TRUE(number.is_pow10());
}

TEST(biginteger_checking, is_pow10_2)
{
    EXPECT_FALSE(big_integer{1024}.is_pow10());
}

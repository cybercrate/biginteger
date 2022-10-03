#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_conversion, to_integer_int_1)
{
    EXPECT_TRUE(big_integer{std::numeric_limits<int>::min()}.to_integer<int>().has_value());
}

TEST(biginteger_conversion, to_integer_int_2)
{
    EXPECT_TRUE(big_integer{std::numeric_limits<int>::max()}.to_integer<int>().has_value());
}

TEST(biginteger_conversion, to_integer_int_3)
{
    EXPECT_FALSE(big_integer{2147483648}.to_integer<int>().has_value());
}

TEST(biginteger_conversion, to_integer_int_4)
{
    EXPECT_FALSE(big_integer{-2147483649}.to_integer<int>().has_value());
}



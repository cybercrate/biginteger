#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_conversion, to_int_1)
{
    EXPECT_TRUE(big_integer{2147483647}.to_int().has_value());
}

TEST(biginteger_conversion, to_int_2)
{
    EXPECT_FALSE(big_integer{2147483648}.to_int().has_value());
}

TEST(biginteger_conversion, to_int64_1)
{
    EXPECT_TRUE(big_integer{9223372036854775807}.to_int64().has_value());
}

TEST(biginteger_conversion, to_int64_2)
{
    EXPECT_FALSE(big_integer{"9223372036854775808"}.to_int64().has_value());
}

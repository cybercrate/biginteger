#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_conversion, to_integer_int64_1)
{
    EXPECT_TRUE(big_integer{std::numeric_limits<std::int64_t>::min()}
        .to_integer<std::int64_t>().has_value());
}

TEST(biginteger_conversion, to_integer_int64_2)
{
    EXPECT_TRUE(big_integer{std::numeric_limits<std::int64_t>::max()}
        .to_integer<std::int64_t>().has_value());
}

TEST(biginteger_conversion, to_integer_int64_3)
{
    EXPECT_FALSE(big_integer{"9223372036854775808"}.to_integer<std::int64_t>().has_value());
}

TEST(biginteger_conversion, to_integer_int64_4)
{
    EXPECT_FALSE(big_integer{"-9223372036854775809"}.to_integer<std::int64_t>().has_value());

}

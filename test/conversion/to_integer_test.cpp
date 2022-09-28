#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_conversion, to_integer_int_1) {
    EXPECT_TRUE(big_integer{2147483647}.to_integer<int>().has_value());
}

TEST(biginteger_conversion, to_integer_int_2) {
    EXPECT_FALSE(big_integer{2147483648}.to_integer<int>().has_value());
}

TEST(biginteger_conversion, to_integer_long_long_1) {
    EXPECT_TRUE(big_integer{9223372036854775807}.to_integer<std::int64_t>().has_value());
}

TEST(biginteger_conversion, to_integer_long_long_2) {
    EXPECT_FALSE(big_integer{"9223372036854775808"}.to_integer<std::int64_t>().has_value());
}

TEST(biginteger_conversion, to_integer_unsigned_long_long_1) {
    EXPECT_TRUE(big_integer{18446744073709551615UL}.to_integer<std::uint64_t>().has_value());
}

TEST(biginteger_conversion, to_integer_unsigned_long_long_2) {
    EXPECT_FALSE(big_integer{"18446744073709551616"}.to_integer<std::uint64_t>().has_value());
}

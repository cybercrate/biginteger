#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_modification, shift_right_1)
{
    EXPECT_EQ(32, big_integer{8192}.shift_right(8));
}

TEST(biginteger_modification, shift_right_2)
{
    EXPECT_EQ(16, big_integer{16384}.shift_right(10));
}

TEST(biginteger_modification, shift_right_throw)
{
    EXPECT_THROW(auto temp = big_integer{10}.shift_right(-2), std::invalid_argument);
}

#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_modification, shift_left_1)
{
    EXPECT_EQ(40, big_integer{10}.shift_left(2));
}

TEST(biginteger_modification, shift_left_shift_2)
{
    EXPECT_EQ(4096, big_integer{512}.shift_left(3));
}

TEST(biginteger_modification, shift_left_throw)
{
    EXPECT_THROW(auto temp = big_integer{10}.shift_left(-2), std::invalid_argument);
}

#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_constructing, from_integral_assignment_operator)
{
    big_integer number = 2048;
    EXPECT_EQ(number, 2048);
}

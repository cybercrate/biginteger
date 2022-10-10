#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_construction, from_char_pointer_constructor)
{
    EXPECT_EQ(big_integer{"2048"}, 2048);
}
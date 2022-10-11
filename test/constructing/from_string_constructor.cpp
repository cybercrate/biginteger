#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_constructing, from_string_constructor)
{
    std::string value{"2048"};
    big_integer number{value};

    EXPECT_EQ(number, 2048);
}

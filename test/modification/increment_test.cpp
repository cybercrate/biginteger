#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_modification, increment_prefix)
{
    EXPECT_EQ(257, ++big_integer{256});
}

TEST(biginteger_modification, increment_postfix)
{
    big_integer number{512};

    auto temp = number++;
    auto decremented_value = number;

    EXPECT_EQ(temp, 512);
    EXPECT_EQ(decremented_value, 513);
}

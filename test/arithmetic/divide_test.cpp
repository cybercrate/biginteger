#include "big_integer/big_integer.h"

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_arithmetic, operator_divide_pp)
{
    EXPECT_EQ(1, big_integer{1024} / 1024);
}

TEST(biginteger_arithmetic, operator_divide_pn)
{
    EXPECT_EQ(-1, big_integer{1024} / -1024);
}

TEST(biginteger_arithmetic, operator_divide_np)
{
    EXPECT_EQ(-1, big_integer{-1024} / 1024);
}

TEST(biginteger_arithmetic, operator_divide_nn)
{
    EXPECT_EQ(1, big_integer{-1024} / -1024);
}

TEST(biginteger_arithmetic, divide_pp)
{
    EXPECT_EQ(1, big_integer{1024}.divide(1024));
}

TEST(biginteger_arithmetic, divide_pn)
{
    EXPECT_EQ(-1, big_integer{1024}.divide(-1024));
}

TEST(biginteger_arithmetic, divide_np)
{
    EXPECT_EQ(-1, big_integer{-1024}.divide(1024));
}

TEST(biginteger_arithmetic, divide_nn)
{
    EXPECT_EQ(1, big_integer{-1024}.divide(-1024));
}

TEST(biginteger_arithmetic, divide_throw)
{
    EXPECT_THROW(big_integer{} / 0, std::invalid_argument);
}

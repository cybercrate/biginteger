#include "big_integer/big_integer.h"

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_arithmetic, operator_plus_pp)
{
    EXPECT_EQ(2048, big_integer{1024} + 1024);
}

TEST(biginteger_arithmetic, operator_plus_pn)
{
    EXPECT_EQ(0, big_integer{1024} + -1024);
}

TEST(biginteger_arithmetic, operator_plus_np)
{
    EXPECT_EQ(0, big_integer{-1024} + 1024);
}

TEST(biginteger_arithmetic, operator_plus_nn)
{
    EXPECT_EQ(-2048, big_integer{-1024} + -1024);
}

TEST(biginteger_arithmetic, add_pp)
{
    EXPECT_EQ(2048, big_integer{1024}.add(1024));
}

TEST(biginteger_arithmetic, add_pn)
{
    EXPECT_EQ(0, big_integer{1024}.add(-1024));
}

TEST(biginteger_arithmetic, add_np)
{
    EXPECT_EQ(0, big_integer{-1024}.add(1024));
}

TEST(biginteger_arithmetic, add_nn)
{
    EXPECT_EQ(-2048, big_integer{-1024}.add(-1024));
}

#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_math, sqrt_1) {
    EXPECT_EQ(big_integer{64}.sqrt(), 8);
}

TEST(biginteger_math, sqrt_2) {
    EXPECT_EQ(big_integer{104857600}.sqrt(), 10240);
}

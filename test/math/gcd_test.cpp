#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_math, gcd_1) {
    EXPECT_EQ(2 * 3, big_integer{2 * 2 * 3}.gcd(2 * 3 * 3));
}

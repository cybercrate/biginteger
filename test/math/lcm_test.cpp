#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_math, lcm_1) {
    EXPECT_EQ(2 * 2 * 3 * 3, big_integer{2 * 2 * 3}.lcm(2 * 3 * 3));
}

TEST(biginteger_math, lcm_3) {
    EXPECT_EQ(225, big_integer{45}.lcm(75));
}

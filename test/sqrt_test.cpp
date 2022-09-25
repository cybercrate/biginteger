#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, sqrt) {
    EXPECT_EQ(big_integer{64}.sqrt(), 8);
}

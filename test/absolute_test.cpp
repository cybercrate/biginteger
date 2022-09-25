#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, abs_positive) {
    EXPECT_EQ(1782737, big_integer{1782737}.abs());
}

TEST(big_integer, abs_negative) {
    EXPECT_EQ(327327389182, big_integer{-327327389182}.abs());
}

TEST(big_integer, abs_zero) {
    EXPECT_EQ(0, big_integer{}.abs());
}

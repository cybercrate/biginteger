#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, is_positive_1) {
    EXPECT_FALSE(big_integer{-512}.is_positive());
}

TEST(big_integer, is_positive_2) {
    EXPECT_TRUE(big_integer{256}.is_positive());
}

TEST(big_integer, is_positive_zero) {
    EXPECT_TRUE(big_integer{0}.is_positive());
}

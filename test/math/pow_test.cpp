#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_math, pow_1) {
    EXPECT_EQ(big_integer{256}.pow(9), "4722366482869645213696");
}

TEST(biginteger_math, pow_2) {
    EXPECT_EQ(big_integer{256}.pow(0), 1);
}

TEST(biginteger_math, pow_3) {
    EXPECT_EQ(big_integer{0}.pow(64), 0);
}

TEST(biginteger_math, pow_4) {
    EXPECT_EQ(big_integer{-1}.pow(-64), -1);
}

TEST(biginteger_math, pow_5) {
    EXPECT_EQ(big_integer{-128}.pow(-64), 0);
}

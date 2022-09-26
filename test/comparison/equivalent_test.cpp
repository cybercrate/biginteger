#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_comparison, equivalent_1) {
    EXPECT_TRUE(big_integer{1024} == big_integer{1024});
}

TEST(biginteger_comparison, equivalent_2) {
    EXPECT_TRUE(big_integer{-256} == big_integer{-256});
}

TEST(biginteger_comparison, equivalent_3) {
    EXPECT_TRUE(big_integer{0} == big_integer{0});
}

TEST(biginteger_comparison, equivalent_4) {
    EXPECT_FALSE(big_integer{1} == big_integer{-1});
}

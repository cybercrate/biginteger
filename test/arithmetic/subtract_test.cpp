#include "big_integer/big_integer.h"

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_arithmetic, operator_minus_pp) {
    EXPECT_EQ(0, big_integer{1024} - 1024);
}

TEST(biginteger_arithmetic, operator_minus_pn) {
    EXPECT_EQ(2048, big_integer{1024} - -1024);
}

TEST(biginteger_arithmetic, operator_minus_np) {
    EXPECT_EQ(-2048, big_integer{-1024} - 1024);
}

TEST(biginteger_arithmetic, operator_minus_nn) {
    EXPECT_EQ(0, big_integer{-1024} - -1024);
}

TEST(biginteger_arithmetic, subtract_pp_1) {
    EXPECT_EQ(0, big_integer{1024}.subtract(1024));
}

TEST(biginteger_arithmetic, subtract_pp_2) {
    EXPECT_EQ(0, big_integer::subtract(1024, 1024));
}

TEST(biginteger_arithmetic, subtract_pn_1) {
    EXPECT_EQ(2048, big_integer{1024}.subtract(-1024));
}

TEST(biginteger_arithmetic, subtract_pn_2) {
    EXPECT_EQ(2048, big_integer::subtract(1024, -1024));
}

TEST(biginteger_arithmetic, subtract_np_1) {
    EXPECT_EQ(-2048, big_integer{-1024}.subtract(1024));
}

TEST(biginteger_arithmetic, subtract_np_2) {
    EXPECT_EQ(-2048, big_integer::subtract(-1024, 1024));
}

TEST(biginteger_arithmetic, subtract_nn_1) {
    EXPECT_EQ(0, big_integer{-1024}.subtract(-1024));
}

TEST(biginteger_arithmetic, subtract_nn_2) {
    EXPECT_EQ(0, big_integer::subtract(-1024, -1024));
}

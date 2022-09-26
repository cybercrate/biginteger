#include "big_integer/big_integer.h"

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_arithmetic, operator_multiply_pp) {
    EXPECT_EQ(1'048'576, big_integer{1024} * 1024);
}

TEST(biginteger_arithmetic, operator_multiply_pn) {
    EXPECT_EQ(-1'048'576, big_integer{1024} * -1024);
}

TEST(biginteger_arithmetic, operator_multiply_np) {
    EXPECT_EQ(-1'048'576, big_integer{-1024} * 1024);
}

TEST(biginteger_arithmetic, operator_multiply_nn) {
    EXPECT_EQ(1'048'576, big_integer{-1024} * -1024);
}

TEST(biginteger_arithmetic, multiply_pp_1) {
    EXPECT_EQ(1'048'576, big_integer{1024}.multiply(1024));
}

TEST(biginteger_arithmetic, multiply_pp_2) {
    EXPECT_EQ(1'048'576, big_integer::multiply(1024, 1024));
}

TEST(biginteger_arithmetic, multiply_pn_1) {
    EXPECT_EQ(-1'048'576, big_integer{1024}.multiply(-1024));
}

TEST(biginteger_arithmetic, multiply_pn_2) {
    EXPECT_EQ(-1'048'576, big_integer::multiply(1024, -1024));
}

TEST(biginteger_arithmetic, multiply_np_1) {
    EXPECT_EQ(-1'048'576, big_integer{-1024}.multiply(1024));
}

TEST(biginteger_arithmetic, multiply_np_2) {
    EXPECT_EQ(-1'048'576, big_integer::multiply(-1024, 1024));
}

TEST(biginteger_arithmetic, multiply_nn_1) {
    EXPECT_EQ(1'048'576, big_integer{-1024}.multiply(-1024));
}

TEST(biginteger_arithmetic, multiply_nn_2) {
    EXPECT_EQ(1'048'576, big_integer::multiply(-1024, -1024));
}

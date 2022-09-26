#include "big_integer/big_integer.h"

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_arithmetic, operator_plus_pp) {
    EXPECT_EQ(2048, big_integer{1024} + 1024);
}

TEST(biginteger_arithmetic, operator_plus_pn) {
    EXPECT_EQ(0, big_integer{1024} + -1024);
}

TEST(biginteger_arithmetic, operator_plus_np) {
    EXPECT_EQ(0, big_integer{-1024} + 1024);
}

TEST(biginteger_arithmetic, operator_plus_nn) {
    EXPECT_EQ(-2048, big_integer{-1024} + -1024);
}

TEST(biginteger_arithmetic, add_pp_1) {
    EXPECT_EQ(2048, big_integer{1024}.add(1024));
}

TEST(biginteger_arithmetic, add_pp_2) {
    EXPECT_EQ(2048, big_integer::add(1024, 1024));
}

TEST(biginteger_arithmetic, add_pn_1) {
    EXPECT_EQ(0, big_integer{1024}.add(-1024));
}

TEST(biginteger_arithmetic, add_pn_2) {
    EXPECT_EQ(0, big_integer::add(1024, -1024));
}

TEST(biginteger_arithmetic, add_np_1) {
    EXPECT_EQ(0, big_integer{-1024}.add(1024));
}

TEST(biginteger_arithmetic, add_np_2) {
    EXPECT_EQ(0, big_integer::add(-1024, 1024));
}

TEST(biginteger_arithmetic, add_nn_1) {
    EXPECT_EQ(-2048, big_integer{-1024}.add(-1024));
}

TEST(biginteger_arithmetic, add_nn_2) {
    EXPECT_EQ(-2048, big_integer::add(-1024, -1024));
}

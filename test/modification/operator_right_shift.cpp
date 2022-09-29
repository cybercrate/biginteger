#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_modification, operator_right_shift_1) {
    EXPECT_EQ(32, big_integer{8192}.right_shift(8));
}

TEST(biginteger_modification, operator_right_shift_2) {
    EXPECT_EQ(16, big_integer{16384}.right_shift(10));
}

TEST(biginteger_modification, operator_right_shift_throw) {
    EXPECT_THROW(big_integer{10}.right_shift(-2), std::invalid_argument);
}

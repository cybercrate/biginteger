#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_modification, operator_left_shift_1) {
    EXPECT_EQ(40, big_integer{10}.left_shift(2));
}

TEST(biginteger_modification, operator_left_shift_2) {
    EXPECT_EQ(4096, big_integer{512}.left_shift(3));
}

TEST(biginteger_modification, operator_left_shift_throw) {
    EXPECT_THROW(big_integer{10}.left_shift(-2), std::invalid_argument);
}

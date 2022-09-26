#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_modification, left_shift_1) {
    EXPECT_EQ(40, big_integer{10} << 2);
}

TEST(biginteger_modification, left_shift_2) {
    EXPECT_EQ(4096, big_integer{512} << 3);
}

TEST(biginteger_modification, right_shift_1) {
    EXPECT_EQ(32, big_integer{8192} >> 8);
}

TEST(biginteger_modification, right_shift_2) {
    EXPECT_EQ(16, big_integer{16384} >> 10);
}

TEST(biginteger_modification, left_shift_throw) {
    EXPECT_THROW(big_integer{10} << -2, std::invalid_argument);
}

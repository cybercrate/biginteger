#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, mod_1) {
    EXPECT_EQ(big_integer{64} % 8, 0);
}

TEST(big_integer, mod_2) {
    EXPECT_EQ(big_integer{29} % 3, 2);
}

TEST(big_integer, mod_throw) {
    EXPECT_THROW(big_integer{} % 0, std::invalid_argument);
}

#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_math, mod_1) {
    EXPECT_EQ(big_integer{64} % 8, 0);
}

TEST(biginteger_math, mod_2) {
    EXPECT_EQ(big_integer{29} % 3, 2);
}

TEST(biginteger_math, mod_3) {
    EXPECT_EQ(big_integer::mod(64, 8), 0);
}

TEST(biginteger_math, mod_throw) {
    EXPECT_THROW(big_integer{} % 0, std::invalid_argument);
}

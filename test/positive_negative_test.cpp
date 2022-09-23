#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, positive_negative) {
    big_integer big_number1{739928192};
    big_integer big_number2{-673282193};

    EXPECT_TRUE(big_number1.is_positive());
    EXPECT_FALSE(big_number1.is_negative());

    EXPECT_TRUE(big_number2.is_negative());
    EXPECT_FALSE(big_number2.is_positive());
}

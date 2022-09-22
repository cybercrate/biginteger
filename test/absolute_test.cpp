#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, abs) {
    big_integer big_number1{327327389182};
    big_integer big_number2{-213792173712};

    EXPECT_EQ(327327389182, big_number1.abs());
    EXPECT_EQ(213792173712, big_number2.abs());
}

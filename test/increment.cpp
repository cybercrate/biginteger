#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, increment) {
    big_integer big_number1{256};
    big_integer big_number2{512};

    auto value1 = ++big_number1;
    auto temp = big_number2++;
    auto value2 = big_number2;

    EXPECT_EQ(value1, big_integer{257});
    EXPECT_EQ(temp, big_integer{512});
    EXPECT_EQ(value2, big_integer{513});
}

#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_modification, swap_1) {
    big_integer number1{739928192};
    big_integer number2{673282193};

    number1.swap(number2);

    EXPECT_EQ(number1, 673282193);
    EXPECT_EQ(number2, 739928192);
}

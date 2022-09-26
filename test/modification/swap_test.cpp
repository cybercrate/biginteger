#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_modification, swap_1) {
    big_integer big_number1{739928192};
    big_integer big_number2{673282193};

    big_number1.swap(big_number2);

    EXPECT_EQ(big_number1, 673282193);
    EXPECT_EQ(big_number2, 739928192);
}

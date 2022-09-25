#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, decrement_prefix) {
    EXPECT_EQ(255, --big_integer{256});
}

TEST(big_integer, decrement_postfix) {
    big_integer number{512};

    auto temp = number--;
    auto decremented_value = number;

    EXPECT_EQ(temp, 512);
    EXPECT_EQ(decremented_value, 511);
}

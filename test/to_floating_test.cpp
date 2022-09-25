#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, to_floating_float_1) {
    auto number = big_integer{673282193}.to_floating<float>().value();
    EXPECT_EQ(number, 673282193.0f);
}

TEST(big_integer, to_floating_float_2) {
    auto number = big_integer{"739928192372838230298302983929329839289380123128301736654324233223"}
        .to_floating<float>();

    EXPECT_FALSE(number.has_value());
}

TEST(big_integer, to_floating_double_1) {
    auto number = big_integer{673282193}.to_floating<double>().value();
    EXPECT_EQ(number, 673282193.0);
}

TEST(big_integer, to_floating_double_2) {
    auto number = big_integer{"739928192372838230298302983929329839289380123128301736654324233223"}
        .to_floating<double>();

    EXPECT_TRUE(number.has_value());
}

TEST(big_integer, to_floating_long_double_1) {
    auto number = big_integer{673282193}.to_floating<long double>().value();
    EXPECT_EQ(number, 673282193.0L);
}

TEST(big_integer, to_floating_long_double_2) {
    auto number = big_integer{"739928192372838230298302983929329839289380123128301736654324233223"}
        .to_floating<long double>();

    EXPECT_TRUE(number.has_value());
}

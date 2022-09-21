#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, to_integer) {
    big_integer big_number1{"73992819237283823029830298392932983928938901231283017473489183"};
    big_integer big_number2{"673282193"};

    auto integer1 = big_number1.to_integer<int>();
    auto integer2 = big_number2.to_integer<int>();

    EXPECT_FALSE(integer1.has_value());
    EXPECT_TRUE(integer2.has_value());

    EXPECT_EQ(integer2.value(), 673282193);
}

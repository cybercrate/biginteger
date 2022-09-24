#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, to_floating_f) {
    big_integer big_number1{"73992819237283823029830298392932983928938901231283017473489183"};
    big_integer big_number2{673282193};

    auto floating1 = big_number1.to_floating<float>();
    auto floating2 = big_number2.to_floating<float>();

    EXPECT_FALSE(floating1.has_value());
    EXPECT_TRUE(floating2.has_value());

    EXPECT_EQ(floating2.value(), 673282193.0f);
}

TEST(big_integer, to_floating_d) {
    big_integer big_number1{"73992819237283823029830298392932983928938901231283017473489183"};
    big_integer big_number2{673282193};

    auto floating1 = big_number1.to_floating<double>();
    auto floating2 = big_number2.to_floating<double>();

    EXPECT_TRUE(floating1.has_value());
    EXPECT_TRUE(floating2.has_value());

    EXPECT_EQ(floating2.value(), 673282193.0);
}

TEST(big_integer, to_floating_ld) {
    big_integer big_number1{"73992819237283823029830298392932983928938901231283017473489183"};
    big_integer big_number2{673282193};

    auto floating1 = big_number1.to_floating<long double>();
    auto floating2 = big_number2.to_floating<long double>();

    EXPECT_TRUE(floating1.has_value());
    EXPECT_TRUE(floating2.has_value());

    EXPECT_EQ(floating2.value(), 673282193.0L);
}

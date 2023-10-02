#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_modification, swap_1) {
    wingmann::numerics::biginteger number1{739'928'192};
    wingmann::numerics::biginteger number2{673'282'193};

    number1.swap(number2);

    EXPECT_EQ(number1, 673'282'193);
    EXPECT_EQ(number2, 739'928'192);
}

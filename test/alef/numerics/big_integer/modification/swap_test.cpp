#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_modification, swap_1) {
    alf::num::big_integer number1{739'928'192};
    alf::num::big_integer number2{673'282'193};

    number1.swap(number2);

    EXPECT_EQ(number1, 673'282'193);
    EXPECT_EQ(number2, 739'928'192);
}

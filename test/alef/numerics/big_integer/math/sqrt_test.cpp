#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_math, sqrt_1) {
    EXPECT_EQ(alf::num::big_integer{64}.sqrt(), 8);
}

TEST(alef_numerics_biginteger_math, sqrt_2) {
    EXPECT_EQ(alf::num::big_integer{104'857'600}.sqrt(), 10'240);
}

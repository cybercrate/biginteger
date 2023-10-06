#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_checking, is_positive_1) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{-512}.isPositive());
}

TEST(wingmann_biginteger_checking, is_positive_2) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{256}.isPositive());
}

TEST(wingmann_biginteger_checking, is_positive_zero) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{0}.isPositive());
}

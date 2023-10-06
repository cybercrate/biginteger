#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_checking, is_negative_1) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{-512}.isNegative());
}

TEST(wingmann_biginteger_checking, is_negative_2) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{256}.isNegative());
}

TEST(wingmann_biginteger_checking, is_negative_zero) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{0}.isNegative());
}

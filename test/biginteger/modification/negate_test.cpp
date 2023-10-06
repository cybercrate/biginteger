#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_modification, operator_tilde_positive) {
    EXPECT_EQ(
        -1'782'737,
        wingmann::numerics::BigInteger{1'782'737}.negate());
}

TEST(wingmann_biginteger_modification, operator_tilde_negative) {
    EXPECT_EQ(
        327'327'389'182,
        wingmann::numerics::BigInteger{-327'327'389'182}.negate());
}

TEST(wingmann_biginteger_modification, operator_tilde_zero) {
    EXPECT_EQ(
        0,
        wingmann::numerics::BigInteger{}.negate());
}

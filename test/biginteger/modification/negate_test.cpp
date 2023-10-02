#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_modification, operator_tilde_positive) {
    EXPECT_EQ(
        -1'782'737,
        wingmann::numerics::biginteger{1'782'737}.negate());
}

TEST(wingmann_biginteger_modification, operator_tilde_negative) {
    EXPECT_EQ(
        327'327'389'182,
        wingmann::numerics::biginteger{-327'327'389'182}.negate());
}

TEST(wingmann_biginteger_modification, operator_tilde_zero) {
    EXPECT_EQ(
        0,
        wingmann::numerics::biginteger{}.negate());
}

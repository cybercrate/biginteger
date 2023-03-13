#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_modification, operator_tilde_positive) {
    EXPECT_EQ(
        -1'782'737,
        alf::num::biginteger{1'782'737}.negate());
}

TEST(alef_numerics_biginteger_modification, operator_tilde_negative) {
    EXPECT_EQ(
        327'327'389'182,
        alf::num::biginteger{-327'327'389'182}.negate());
}

TEST(alef_numerics_biginteger_modification, operator_tilde_zero) {
    EXPECT_EQ(
        0,
        alf::num::biginteger{}.negate());
}

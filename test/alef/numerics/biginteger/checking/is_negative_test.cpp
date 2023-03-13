#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_checking, is_negative_1) {
    EXPECT_TRUE(alf::num::biginteger{-512}.is_negative());
}

TEST(alef_numerics_biginteger_checking, is_negative_2) {
    EXPECT_FALSE(alf::num::biginteger{256}.is_negative());
}

TEST(alef_numerics_biginteger_checking, is_negative_zero) {
    EXPECT_FALSE(alf::num::biginteger{0}.is_negative());
}

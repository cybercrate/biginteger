#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_checking, is_positive_1) {
    EXPECT_FALSE(alf::num::big_integer{-512}.is_positive());
}

TEST(alef_numerics_biginteger_checking, is_positive_2) {
    EXPECT_TRUE(alf::num::big_integer{256}.is_positive());
}

TEST(alef_numerics_biginteger_checking, is_positive_zero) {
    EXPECT_TRUE(alf::num::big_integer{0}.is_positive());
}

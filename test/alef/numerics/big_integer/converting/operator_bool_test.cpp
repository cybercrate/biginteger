#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_converting, operator_bool_positive) {
    EXPECT_TRUE(alf::num::big_integer{1024});
}

TEST(alef_numerics_biginteger_converting, operator_bool_negative) {
    EXPECT_TRUE(alf::num::big_integer{-1024});
}

TEST(alef_numerics_biginteger_converting, operator_bool_zero) {
    EXPECT_FALSE(alf::num::big_integer{0});
}

#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_arithmetic, operator_minus_pp) {
    EXPECT_EQ(0, alf::num::big_integer{1024} - 1024);
}

TEST(alef_numerics_biginteger_arithmetic, operator_minus_pn) {
    EXPECT_EQ(2048, alf::num::big_integer{1024} - -1024);
}

TEST(alef_numerics_biginteger_arithmetic, operator_minus_np) {
    EXPECT_EQ(-2048, alf::num::big_integer{-1024} - 1024);
}

TEST(alef_numerics_biginteger_arithmetic, operator_minus_nn) {
    EXPECT_EQ(0, alf::num::big_integer{-1024} - -1024);
}

TEST(alef_numerics_biginteger_arithmetic, subtract_pp) {
    EXPECT_EQ(0, alf::num::big_integer{1024}.subtract(1024));
}

TEST(alef_numerics_biginteger_arithmetic, subtract_pn) {
    EXPECT_EQ(2048, alf::num::big_integer{1024}.subtract(-1024));
}

TEST(alef_numerics_biginteger_arithmetic, subtract_np) {
    EXPECT_EQ(-2048, alf::num::big_integer{-1024}.subtract(1024));
}

TEST(alef_numerics_biginteger_arithmetic, subtract_nn) {
    EXPECT_EQ(0, alf::num::big_integer{-1024}.subtract(-1024));
}

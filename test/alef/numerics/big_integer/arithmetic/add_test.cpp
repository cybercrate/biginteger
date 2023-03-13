#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_arithmetic, operator_plus_pp) {
    EXPECT_EQ(2048, alf::num::big_integer{1024} + 1024);
}

TEST(alef_numerics_biginteger_arithmetic, operator_plus_pn) {
    EXPECT_EQ(0, alf::num::big_integer{1024} + -1024);
}

TEST(alef_numerics_biginteger_arithmetic, operator_plus_np) {
    EXPECT_EQ(0, alf::num::big_integer{-1024} + 1024);
}

TEST(alef_numerics_biginteger_arithmetic, operator_plus_nn) {
    EXPECT_EQ(-2048, alf::num::big_integer{-1024} + -1024);
}

TEST(alef_numerics_biginteger_arithmetic, add_pp) {
    EXPECT_EQ(2048, alf::num::big_integer{1024}.add(1024));
}

TEST(alef_numerics_biginteger_arithmetic, add_pn) {
    EXPECT_EQ(0, alf::num::big_integer{1024}.add(-1024));
}

TEST(alef_numerics_biginteger_arithmetic, add_np) {
    EXPECT_EQ(0, alf::num::big_integer{-1024}.add(1024));
}

TEST(alef_numerics_biginteger_arithmetic, add_nn) {
    EXPECT_EQ(-2048, alf::num::big_integer{-1024}.add(-1024));
}

#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_arithmetic, operator_mod) {
    EXPECT_EQ(alf::num::big_integer{64} % 8, 0);
}

TEST(alef_numerics_biginteger_arithmetic, mod) {
    EXPECT_EQ(0, alf::num::big_integer{64}.mod(8));
}

TEST(alef_numerics_biginteger_arithmetic, operator_mod_throw) {
    EXPECT_THROW(alf::num::big_integer{} % 0, std::invalid_argument);
}

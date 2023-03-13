#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_math, gcd_1) {
    EXPECT_EQ(2 * 3, alf::num::big_integer{2 * 2 * 3}.gcd(2 * 3 * 3));
}

#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_math, gcd_1) {
    EXPECT_EQ(2 * 3, alf::num::biginteger{2 * 2 * 3}.gcd(2 * 3 * 3));
}

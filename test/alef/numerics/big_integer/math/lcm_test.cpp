#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_math, lcm_1) {
    EXPECT_EQ(2 * 2 * 3 * 3, alf::num::big_integer{2 * 2 * 3}.lcm(2 * 3 * 3));
}

TEST(alef_numerics_biginteger_math, lcm_3) {
    EXPECT_EQ(225, alf::num::big_integer{45}.lcm(75));
}

#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_math, lcm_1) {
    EXPECT_EQ(2 * 2 * 3 * 3, alf::num::biginteger{2 * 2 * 3}.lcm(2 * 3 * 3));
}

TEST(alef_numerics_biginteger_math, lcm_3) {
    EXPECT_EQ(225, alf::num::biginteger{45}.lcm(75));
}

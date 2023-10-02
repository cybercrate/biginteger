#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_math, lcm_1) {
    EXPECT_EQ(2 * 2 * 3 * 3, wingmann::numerics::biginteger{2 * 2 * 3}.lcm(2 * 3 * 3));
}

TEST(wingmann_biginteger_math, lcm_3) {
    EXPECT_EQ(225, wingmann::numerics::biginteger{45}.lcm(75));
}

#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_math, gcd_1) {
    EXPECT_EQ(2 * 3, wingmann::numerics::biginteger{2 * 2 * 3}.gcd(2 * 3 * 3));
}

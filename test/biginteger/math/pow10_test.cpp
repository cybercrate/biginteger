#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_math, pow10_1) {
    EXPECT_EQ(
        wingmann::numerics::biginteger{16}.pow10(),
        "10000000000000000");
}

TEST(wingmann_biginteger_math, pow10_2) {
    EXPECT_EQ(
        wingmann::numerics::biginteger{64}.pow10(),
        "10000000000000000000000000000000000000000000000000000000000000000");
}

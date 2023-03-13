#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_math, pow10_1) {
    EXPECT_EQ(
        alf::num::biginteger{16}.pow10(),
        "10000000000000000");
}

TEST(alef_numerics_biginteger_math, pow10_2) {
    EXPECT_EQ(
        alf::num::biginteger{64}.pow10(),
        "10000000000000000000000000000000000000000000000000000000000000000");
}

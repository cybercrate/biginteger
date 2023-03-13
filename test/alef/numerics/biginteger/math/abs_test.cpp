#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_math, abs_positive_1) {
    EXPECT_EQ(1782737, alf::num::biginteger{1782737}.abs());
}

TEST(alef_numerics_biginteger_math, abs_negative_1) {
    EXPECT_EQ(327327389182, alf::num::biginteger{-327327389182}.abs());
}

TEST(alef_numerics_biginteger_math, abs_zero_1) {
    EXPECT_EQ(0, alf::num::biginteger{}.abs());
}

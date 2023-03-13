#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_math, abs_positive_1) {
    EXPECT_EQ(1782737, alf::num::big_integer{1782737}.abs());
}

TEST(alef_numerics_biginteger_math, abs_negative_1) {
    EXPECT_EQ(327327389182, alf::num::big_integer{-327327389182}.abs());
}

TEST(alef_numerics_biginteger_math, abs_zero_1) {
    EXPECT_EQ(0, alf::num::big_integer{}.abs());
}

#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_math, abs_positive_1) {
    EXPECT_EQ(1782737, wingmann::numerics::biginteger{1782737}.abs());
}

TEST(wingmann_biginteger_math, abs_negative_1) {
    EXPECT_EQ(327327389182, wingmann::numerics::biginteger{-327327389182}.abs());
}

TEST(wingmann_biginteger_math, abs_zero_1) {
    EXPECT_EQ(0, wingmann::numerics::biginteger{}.abs());
}

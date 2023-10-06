#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_math, abs_positive_1) {
    EXPECT_EQ(1782737, wingmann::numerics::BigInteger{1782737}.abs());
}

TEST(wingmann_biginteger_math, abs_negative_1) {
    EXPECT_EQ(327327389182, wingmann::numerics::BigInteger{-327327389182}.abs());
}

TEST(wingmann_biginteger_math, abs_zero_1) {
    EXPECT_EQ(0, wingmann::numerics::BigInteger{}.abs());
}

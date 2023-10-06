#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_math, sqrt_1) {
    EXPECT_EQ(wingmann::numerics::BigInteger{64}.sqrt(), 8);
}

TEST(wingmann_biginteger_math, sqrt_2) {
    EXPECT_EQ(wingmann::numerics::BigInteger{104'857'600}.sqrt(), 10'240);
}

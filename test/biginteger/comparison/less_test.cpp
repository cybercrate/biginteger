#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_comparison, less_1) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{128} < wingmann::numerics::BigInteger{256});
}

TEST(wingmann_biginteger_comparison, less_2) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{-128} < wingmann::numerics::BigInteger{256});
}

TEST(wingmann_biginteger_comparison, less_3) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{-128} < wingmann::numerics::BigInteger{-64});
}

TEST(wingmann_biginteger_comparison, less_4) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{0} < wingmann::numerics::BigInteger{0});
}

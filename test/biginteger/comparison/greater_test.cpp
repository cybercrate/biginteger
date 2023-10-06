#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_comparison, greater_1) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{256} > wingmann::numerics::BigInteger{128});
}

TEST(wingmann_biginteger_comparison, greater_2) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{256} > wingmann::numerics::BigInteger{-128});
}

TEST(wingmann_biginteger_comparison, greater_3) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{-64} > wingmann::numerics::BigInteger{-128});
}

TEST(wingmann_biginteger_comparison, greater_4) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{0} > wingmann::numerics::BigInteger{0});
}

#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_comparison, not_equivalent_1) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{1024} != wingmann::numerics::BigInteger{-1024});
}

TEST(wingmann_biginteger_comparison, not_equivalent_2) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{-256} != wingmann::numerics::BigInteger{256});
}

TEST(wingmann_biginteger_comparison, not_equivalent_3) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{0} != wingmann::numerics::BigInteger{0});
}

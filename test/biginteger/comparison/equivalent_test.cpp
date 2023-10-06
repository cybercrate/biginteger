#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_comparison, equivalent_1) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{1024} == wingmann::numerics::BigInteger{1024});
}

TEST(wingmann_biginteger_comparison, equivalent_2) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{-256} == wingmann::numerics::BigInteger{-256});
}

TEST(wingmann_biginteger_comparison, equivalent_3) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{0} == wingmann::numerics::BigInteger{0});
}

TEST(wingmann_biginteger_comparison, equivalent_4) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{1} == wingmann::numerics::BigInteger{-1});
}

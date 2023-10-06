#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_arithmetic, operator_mod) {
    EXPECT_EQ(wingmann::numerics::BigInteger{64} % 8, 0);
}

TEST(wingmann_biginteger_arithmetic, mod) {
    EXPECT_EQ(0, wingmann::numerics::BigInteger{64}.mod(8));
}

TEST(wingmann_biginteger_arithmetic, operator_mod_throw) {
    EXPECT_THROW(wingmann::numerics::BigInteger{} % 0, std::invalid_argument);
}

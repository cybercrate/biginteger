#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_arithmetic, operator_plus_pp) {
    EXPECT_EQ(2048, wingmann::numerics::BigInteger{1024} + 1024);
}

TEST(wingmann_biginteger_arithmetic, operator_plus_pn) {
    EXPECT_EQ(0, wingmann::numerics::BigInteger{1024} + -1024);
}

TEST(wingmann_biginteger_arithmetic, operator_plus_np) {
    EXPECT_EQ(0, wingmann::numerics::BigInteger{-1024} + 1024);
}

TEST(wingmann_biginteger_arithmetic, operator_plus_nn) {
    EXPECT_EQ(-2048, wingmann::numerics::BigInteger{-1024} + -1024);
}

TEST(wingmann_biginteger_arithmetic, add_pp) {
    EXPECT_EQ(2048, wingmann::numerics::BigInteger{1024}.add(1024));
}

TEST(wingmann_biginteger_arithmetic, add_pn) {
    EXPECT_EQ(0, wingmann::numerics::BigInteger{1024}.add(-1024));
}

TEST(wingmann_biginteger_arithmetic, add_np) {
    EXPECT_EQ(0, wingmann::numerics::BigInteger{-1024}.add(1024));
}

TEST(wingmann_biginteger_arithmetic, add_nn) {
    EXPECT_EQ(-2048, wingmann::numerics::BigInteger{-1024}.add(-1024));
}

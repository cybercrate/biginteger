#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_arithmetic, operator_multiply_pp) {
    EXPECT_EQ(1'048'576, wingmann::numerics::BigInteger{1024} * 1024);
}

TEST(wingmann_biginteger_arithmetic, operator_multiply_pn) {
    EXPECT_EQ(-1'048'576, wingmann::numerics::BigInteger{1024} * -1024);
}

TEST(wingmann_biginteger_arithmetic, operator_multiply_np) {
    EXPECT_EQ(-1'048'576, wingmann::numerics::BigInteger{-1024} * 1024);
}

TEST(wingmann_biginteger_arithmetic, operator_multiply_nn) {
    EXPECT_EQ(1'048'576, wingmann::numerics::BigInteger{-1024} * -1024);
}

TEST(wingmann_biginteger_arithmetic, multiply_pp_1) {
    EXPECT_EQ(1'048'576, wingmann::numerics::BigInteger{1024}.multiply(1024));
}

TEST(wingmann_biginteger_arithmetic, multiply_pn_1) {
    EXPECT_EQ(-1'048'576, wingmann::numerics::BigInteger{1024}.multiply(-1024));
}

TEST(wingmann_biginteger_arithmetic, multiply_np_1) {
    EXPECT_EQ(-1'048'576, wingmann::numerics::BigInteger{-1024}.multiply(1024));
}

TEST(wingmann_biginteger_arithmetic, multiply_nn_1) {
    EXPECT_EQ(1'048'576, wingmann::numerics::BigInteger{-1024}.multiply(-1024));
}

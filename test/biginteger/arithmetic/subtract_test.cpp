#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_arithmetic, operator_minus_pp) {
    EXPECT_EQ(0, wingmann::numerics::biginteger{1024} - 1024);
}

TEST(wingmann_biginteger_arithmetic, operator_minus_pn) {
    EXPECT_EQ(2048, wingmann::numerics::biginteger{1024} - -1024);
}

TEST(wingmann_biginteger_arithmetic, operator_minus_np) {
    EXPECT_EQ(-2048, wingmann::numerics::biginteger{-1024} - 1024);
}

TEST(wingmann_biginteger_arithmetic, operator_minus_nn) {
    EXPECT_EQ(0, wingmann::numerics::biginteger{-1024} - -1024);
}

TEST(wingmann_biginteger_arithmetic, subtract_pp) {
    EXPECT_EQ(0, wingmann::numerics::biginteger{1024}.subtract(1024));
}

TEST(wingmann_biginteger_arithmetic, subtract_pn) {
    EXPECT_EQ(2048, wingmann::numerics::biginteger{1024}.subtract(-1024));
}

TEST(wingmann_biginteger_arithmetic, subtract_np) {
    EXPECT_EQ(-2048, wingmann::numerics::biginteger{-1024}.subtract(1024));
}

TEST(wingmann_biginteger_arithmetic, subtract_nn) {
    EXPECT_EQ(0, wingmann::numerics::biginteger{-1024}.subtract(-1024));
}

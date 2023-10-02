#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_converting, operator_bool_positive) {
    EXPECT_TRUE(wingmann::numerics::biginteger{1024});
}

TEST(wingmann_biginteger_converting, operator_bool_negative) {
    EXPECT_TRUE(wingmann::numerics::biginteger{-1024});
}

TEST(wingmann_biginteger_converting, operator_bool_zero) {
    EXPECT_FALSE(wingmann::numerics::biginteger{0});
}

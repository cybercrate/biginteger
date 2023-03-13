#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_converting, operator_bool_positive) {
    EXPECT_TRUE(alf::num::biginteger{1024});
}

TEST(alef_numerics_biginteger_converting, operator_bool_negative) {
    EXPECT_TRUE(alf::num::biginteger{-1024});
}

TEST(alef_numerics_biginteger_converting, operator_bool_zero) {
    EXPECT_FALSE(alf::num::biginteger{0});
}

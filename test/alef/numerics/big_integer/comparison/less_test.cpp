#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_comparison, less_1) {
    EXPECT_TRUE(alf::num::big_integer{128} < alf::num::big_integer{256});
}

TEST(alef_numerics_biginteger_comparison, less_2) {
    EXPECT_TRUE(alf::num::big_integer{-128} < alf::num::big_integer{256});
}

TEST(alef_numerics_biginteger_comparison, less_3) {
    EXPECT_TRUE(alf::num::big_integer{-128} < alf::num::big_integer{-64});
}

TEST(alef_numerics_biginteger_comparison, less_4) {
    EXPECT_FALSE(alf::num::big_integer{0} < alf::num::big_integer{0});
}

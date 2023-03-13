#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_comparison, greater_1) {
    EXPECT_TRUE(alf::num::big_integer{256} > alf::num::big_integer{128});
}

TEST(alef_numerics_biginteger_comparison, greater_2) {
    EXPECT_TRUE(alf::num::big_integer{256} > alf::num::big_integer{-128});
}

TEST(alef_numerics_biginteger_comparison, greater_3) {
    EXPECT_TRUE(alf::num::big_integer{-64} > alf::num::big_integer{-128});
}

TEST(alef_numerics_biginteger_comparison, greater_4) {
    EXPECT_FALSE(alf::num::big_integer{0} > alf::num::big_integer{0});
}

#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_comparison, equivalent_1) {
    EXPECT_TRUE(alf::num::big_integer{1024} == alf::num::big_integer{1024});
}

TEST(alef_numerics_biginteger_comparison, equivalent_2) {
    EXPECT_TRUE(alf::num::big_integer{-256} == alf::num::big_integer{-256});
}

TEST(alef_numerics_biginteger_comparison, equivalent_3) {
    EXPECT_TRUE(alf::num::big_integer{0} == alf::num::big_integer{0});
}

TEST(alef_numerics_biginteger_comparison, equivalent_4) {
    EXPECT_FALSE(alf::num::big_integer{1} == alf::num::big_integer{-1});
}

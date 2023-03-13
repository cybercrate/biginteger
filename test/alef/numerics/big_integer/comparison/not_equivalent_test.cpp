#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_comparison, not_equivalent_1) {
    EXPECT_TRUE(alf::num::big_integer{1024} != alf::num::big_integer{-1024});
}

TEST(alef_numerics_biginteger_comparison, not_equivalent_2) {
    EXPECT_TRUE(alf::num::big_integer{-256} != alf::num::big_integer{256});
}

TEST(alef_numerics_biginteger_comparison, not_equivalent_3) {
    EXPECT_FALSE(alf::num::big_integer{0} != alf::num::big_integer{0});
}

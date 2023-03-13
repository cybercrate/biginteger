#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_comparison, not_equivalent_1) {
    EXPECT_TRUE(alf::num::biginteger{1024} != alf::num::biginteger{-1024});
}

TEST(alef_numerics_biginteger_comparison, not_equivalent_2) {
    EXPECT_TRUE(alf::num::biginteger{-256} != alf::num::biginteger{256});
}

TEST(alef_numerics_biginteger_comparison, not_equivalent_3) {
    EXPECT_FALSE(alf::num::biginteger{0} != alf::num::biginteger{0});
}

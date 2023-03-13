#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_comparison, greater_1) {
    EXPECT_TRUE(alf::num::biginteger{256} > alf::num::biginteger{128});
}

TEST(alef_numerics_biginteger_comparison, greater_2) {
    EXPECT_TRUE(alf::num::biginteger{256} > alf::num::biginteger{-128});
}

TEST(alef_numerics_biginteger_comparison, greater_3) {
    EXPECT_TRUE(alf::num::biginteger{-64} > alf::num::biginteger{-128});
}

TEST(alef_numerics_biginteger_comparison, greater_4) {
    EXPECT_FALSE(alf::num::biginteger{0} > alf::num::biginteger{0});
}

#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_comparison, less_1) {
    EXPECT_TRUE(alf::num::biginteger{128} < alf::num::biginteger{256});
}

TEST(alef_numerics_biginteger_comparison, less_2) {
    EXPECT_TRUE(alf::num::biginteger{-128} < alf::num::biginteger{256});
}

TEST(alef_numerics_biginteger_comparison, less_3) {
    EXPECT_TRUE(alf::num::biginteger{-128} < alf::num::biginteger{-64});
}

TEST(alef_numerics_biginteger_comparison, less_4) {
    EXPECT_FALSE(alf::num::biginteger{0} < alf::num::biginteger{0});
}

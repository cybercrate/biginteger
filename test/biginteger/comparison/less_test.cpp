#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_comparison, less_1) {
    EXPECT_TRUE(wingmann::numerics::biginteger{128} < wingmann::numerics::biginteger{256});
}

TEST(wingmann_biginteger_comparison, less_2) {
    EXPECT_TRUE(wingmann::numerics::biginteger{-128} < wingmann::numerics::biginteger{256});
}

TEST(wingmann_biginteger_comparison, less_3) {
    EXPECT_TRUE(wingmann::numerics::biginteger{-128} < wingmann::numerics::biginteger{-64});
}

TEST(wingmann_biginteger_comparison, less_4) {
    EXPECT_FALSE(wingmann::numerics::biginteger{0} < wingmann::numerics::biginteger{0});
}

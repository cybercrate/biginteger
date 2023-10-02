#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_comparison, greater_1) {
    EXPECT_TRUE(wingmann::numerics::biginteger{256} > wingmann::numerics::biginteger{128});
}

TEST(wingmann_biginteger_comparison, greater_2) {
    EXPECT_TRUE(wingmann::numerics::biginteger{256} > wingmann::numerics::biginteger{-128});
}

TEST(wingmann_biginteger_comparison, greater_3) {
    EXPECT_TRUE(wingmann::numerics::biginteger{-64} > wingmann::numerics::biginteger{-128});
}

TEST(wingmann_biginteger_comparison, greater_4) {
    EXPECT_FALSE(wingmann::numerics::biginteger{0} > wingmann::numerics::biginteger{0});
}

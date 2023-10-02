#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_comparison, not_equivalent_1) {
    EXPECT_TRUE(wingmann::numerics::biginteger{1024} != wingmann::numerics::biginteger{-1024});
}

TEST(wingmann_biginteger_comparison, not_equivalent_2) {
    EXPECT_TRUE(wingmann::numerics::biginteger{-256} != wingmann::numerics::biginteger{256});
}

TEST(wingmann_biginteger_comparison, not_equivalent_3) {
    EXPECT_FALSE(wingmann::numerics::biginteger{0} != wingmann::numerics::biginteger{0});
}

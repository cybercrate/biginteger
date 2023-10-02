#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_comparison, equivalent_1) {
    EXPECT_TRUE(wingmann::numerics::biginteger{1024} == wingmann::numerics::biginteger{1024});
}

TEST(wingmann_biginteger_comparison, equivalent_2) {
    EXPECT_TRUE(wingmann::numerics::biginteger{-256} == wingmann::numerics::biginteger{-256});
}

TEST(wingmann_biginteger_comparison, equivalent_3) {
    EXPECT_TRUE(wingmann::numerics::biginteger{0} == wingmann::numerics::biginteger{0});
}

TEST(wingmann_biginteger_comparison, equivalent_4) {
    EXPECT_FALSE(wingmann::numerics::biginteger{1} == wingmann::numerics::biginteger{-1});
}

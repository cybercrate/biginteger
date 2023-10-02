#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_arithmetic, operator_mod) {
    EXPECT_EQ(wingmann::numerics::biginteger{64} % 8, 0);
}

TEST(wingmann_biginteger_arithmetic, mod) {
    EXPECT_EQ(0, wingmann::numerics::biginteger{64}.mod(8));
}

TEST(wingmann_biginteger_arithmetic, operator_mod_throw) {
    EXPECT_THROW(wingmann::numerics::biginteger{} % 0, std::invalid_argument);
}

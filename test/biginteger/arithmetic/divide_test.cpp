#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_arithmetic, operator_divide_pp) {
    EXPECT_EQ(1, wingmann::numerics::biginteger{1024} / 1024);
}

TEST(wingmann_biginteger_arithmetic, operator_divide_pn) {
    EXPECT_EQ(-1, wingmann::numerics::biginteger{1024} / -1024);
}

TEST(wingmann_biginteger_arithmetic, operator_divide_np) {
    EXPECT_EQ(-1, wingmann::numerics::biginteger{-1024} / 1024);
}

TEST(wingmann_biginteger_arithmetic, operator_divide_nn) {
    EXPECT_EQ(1, wingmann::numerics::biginteger{-1024} / -1024);
}

TEST(wingmann_biginteger_arithmetic, divide_pp) {
    EXPECT_EQ(1, wingmann::numerics::biginteger{1024}.divide(1024));
}

TEST(wingmann_biginteger_arithmetic, divide_pn) {
    EXPECT_EQ(-1, wingmann::numerics::biginteger{1024}.divide(-1024));
}

TEST(wingmann_biginteger_arithmetic, divide_np) {
    EXPECT_EQ(-1, wingmann::numerics::biginteger{-1024}.divide(1024));
}

TEST(wingmann_biginteger_arithmetic, divide_nn) {
    EXPECT_EQ(1, wingmann::numerics::biginteger{-1024}.divide(-1024));
}

TEST(wingmann_biginteger_arithmetic, divide_throw) {
    EXPECT_THROW(wingmann::numerics::biginteger{} / 0, std::invalid_argument);
}

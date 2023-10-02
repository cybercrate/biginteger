#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_checking, is_negative_1) {
    EXPECT_TRUE(wingmann::numerics::biginteger{-512}.is_negative());
}

TEST(wingmann_biginteger_checking, is_negative_2) {
    EXPECT_FALSE(wingmann::numerics::biginteger{256}.is_negative());
}

TEST(wingmann_biginteger_checking, is_negative_zero) {
    EXPECT_FALSE(wingmann::numerics::biginteger{0}.is_negative());
}

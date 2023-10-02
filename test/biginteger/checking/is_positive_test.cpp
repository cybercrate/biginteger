#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_checking, is_positive_1) {
    EXPECT_FALSE(wingmann::numerics::biginteger{-512}.is_positive());
}

TEST(wingmann_biginteger_checking, is_positive_2) {
    EXPECT_TRUE(wingmann::numerics::biginteger{256}.is_positive());
}

TEST(wingmann_biginteger_checking, is_positive_zero) {
    EXPECT_TRUE(wingmann::numerics::biginteger{0}.is_positive());
}

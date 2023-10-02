#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_math, pow_1) {
    EXPECT_EQ(wingmann::numerics::biginteger{256}.pow(9), "4722366482869645213696");
}

TEST(wingmann_biginteger_math, pow_2) {
    EXPECT_EQ(wingmann::numerics::biginteger{256}.pow(0), 1);
}

TEST(wingmann_biginteger_math, pow_3) {
    EXPECT_EQ(wingmann::numerics::biginteger{0}.pow(64), 0);
}

TEST(wingmann_biginteger_math, pow_4) {
    EXPECT_EQ(wingmann::numerics::biginteger{-1}.pow(-64), -1);
}

TEST(wingmann_biginteger_math, pow_5) {
    EXPECT_EQ(wingmann::numerics::biginteger{-128}.pow(-64), 0);
}

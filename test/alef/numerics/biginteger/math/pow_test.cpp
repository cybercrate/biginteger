#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_math, pow_1) {
    EXPECT_EQ(alf::num::biginteger{256}.pow(9), "4722366482869645213696");
}

TEST(alef_numerics_biginteger_math, pow_2) {
    EXPECT_EQ(alf::num::biginteger{256}.pow(0), 1);
}

TEST(alef_numerics_biginteger_math, pow_3) {
    EXPECT_EQ(alf::num::biginteger{0}.pow(64), 0);
}

TEST(alef_numerics_biginteger_math, pow_4) {
    EXPECT_EQ(alf::num::biginteger{-1}.pow(-64), -1);
}

TEST(alef_numerics_biginteger_math, pow_5) {
    EXPECT_EQ(alf::num::biginteger{-128}.pow(-64), 0);
}

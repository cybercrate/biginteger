#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_checking, is_pow10_1) {
    alf::num::biginteger number{"100000000000000000000000000000000000000000000000000000000000000"};
    EXPECT_TRUE(number.is_pow10());
}

TEST(alef_numerics_biginteger_checking, is_pow10_2) {
    EXPECT_FALSE(alf::num::biginteger{1024}.is_pow10());
}

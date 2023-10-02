#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_checking, is_pow10_1) {
    wingmann::numerics::biginteger number{"100000000000000000000000000000000000000000000000000000000000000"};
    EXPECT_TRUE(number.is_pow10());
}

TEST(wingmann_biginteger_checking, is_pow10_2) {
    EXPECT_FALSE(wingmann::numerics::biginteger{1024}.is_pow10());
}

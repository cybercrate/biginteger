#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_checking, is_pow10_1) {
    wingmann::numerics::BigInteger number{"100000000000000000000000000000000000000000000000000000000000000"};
    EXPECT_TRUE(number.isPow10());
}

TEST(wingmann_biginteger_checking, is_pow10_2) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{1024}.isPow10());
}

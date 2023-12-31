#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

#include <iostream>

TEST(wingmann_biginteger_converting, to_integer_int64_1) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{0}
        .to_int64()
        .has_value());
}

TEST(wingmann_biginteger_converting, to_integer_int64_2) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{std::numeric_limits<std::int64_t>::max()}
        .to_int64()
        .has_value());
}

TEST(wingmann_biginteger_converting, to_integer_int64_3) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{"9223372036854775808"}
        .to_int64()
        .has_value());
}

TEST(wingmann_biginteger_converting, to_integer_int64_4) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{"-9223372036854775809"}
        .to_int64()
        .has_value());
}

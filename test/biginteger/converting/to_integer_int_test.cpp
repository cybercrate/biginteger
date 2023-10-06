#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_converting, to_integer_int_1) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{0}
        .to_int32()
        .has_value());
}

TEST(wingmann_biginteger_converting, to_integer_int_2) {
    EXPECT_TRUE(wingmann::numerics::BigInteger{std::numeric_limits<std::int32_t>::max()}
        .to_int32()
        .has_value());
}

TEST(wingmann_biginteger_converting, to_integer_int_3) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{2'147'483'648}
        .to_int32()
        .has_value());
}

TEST(wingmann_biginteger_converting, to_integer_int_4) {
    EXPECT_FALSE(wingmann::numerics::BigInteger{-2'147'483'649}
        .to_int32()
        .has_value());
}



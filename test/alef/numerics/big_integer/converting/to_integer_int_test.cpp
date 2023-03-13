#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_converting, to_integer_int_1) {
    EXPECT_TRUE(alf::num::big_integer{std::numeric_limits<alf::int32>::min()}
        .to_int32()
        .has_value());
}

TEST(alef_numerics_biginteger_converting, to_integer_int_2) {
    EXPECT_TRUE(alf::num::big_integer{std::numeric_limits<alf::int32>::max()}
        .to_int32()
        .has_value());
}

TEST(alef_numerics_biginteger_converting, to_integer_int_3) {
    EXPECT_FALSE(alf::num::big_integer{2'147'483'648}
        .to_int32()
        .has_value());
}

TEST(alef_numerics_biginteger_converting, to_integer_int_4) {
    EXPECT_FALSE(alf::num::big_integer{-2'147'483'649}
        .to_int32()
        .has_value());
}



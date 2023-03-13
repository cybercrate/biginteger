#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_converting, to_integer_int64_1) {
    EXPECT_TRUE(alf::num::biginteger{std::numeric_limits<alf::int64>::min()}
        .to_int64()
        .has_value());
}

TEST(alef_numerics_biginteger_converting, to_integer_int64_2) {
    EXPECT_TRUE(alf::num::biginteger{std::numeric_limits<alf::int64>::max()}
        .to_int64()
        .has_value());
}

TEST(alef_numerics_biginteger_converting, to_integer_int64_3) {
    EXPECT_FALSE(alf::num::biginteger{"9223372036854775808"}
        .to_int64()
        .has_value());
}

TEST(alef_numerics_biginteger_converting, to_integer_int64_4) {
    EXPECT_FALSE(alf::num::biginteger{"-9223372036854775809"}
        .to_int64()
        .has_value());
}

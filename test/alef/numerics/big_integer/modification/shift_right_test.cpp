#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_modification, shift_right_1) {
    EXPECT_EQ(
        32,
        alf::num::big_integer{8192}.shift_right(8));
}

TEST(alef_numerics_biginteger_modification, shift_right_2) {
    EXPECT_EQ(
        16,
        alf::num::big_integer{16'384}.shift_right(10));
}

TEST(alef_numerics_biginteger_modification, shift_right_throw) {
    EXPECT_THROW(
        auto temp = alf::num::big_integer{10}.shift_right(-2),
        std::invalid_argument);
}

#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_modification, shift_left_1) {
    EXPECT_EQ(
        40,
        alf::num::big_integer{10}.shift_left(2));
}

TEST(alef_numerics_biginteger_modification, shift_left_shift_2) {
    EXPECT_EQ(
        4096,
        alf::num::big_integer{512}.shift_left(3));
}

TEST(alef_numerics_biginteger_modification, shift_left_throw) {
    EXPECT_THROW(
        auto temp = alf::num::big_integer{10}.shift_left(-2),
        std::invalid_argument);
}

#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_modification, shift_left_1) {
    EXPECT_EQ(
        40,
        wingmann::numerics::BigInteger{10}.shiftLeft(2));
}

TEST(wingmann_biginteger_modification, shift_left_shift_2) {
    EXPECT_EQ(
        4096,
        wingmann::numerics::BigInteger{512}.shiftLeft(3));
}

TEST(wingmann_biginteger_modification, shift_left_throw) {
    EXPECT_THROW(
        auto temp = wingmann::numerics::BigInteger{10}.shiftLeft(-2),
        std::invalid_argument);
}

#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_modification, shift_right_1) {
    EXPECT_EQ(
        32,
        wingmann::numerics::BigInteger{8192}.shiftRight(8));
}

TEST(wingmann_biginteger_modification, shift_right_2) {
    EXPECT_EQ(
        16,
        wingmann::numerics::BigInteger{16'384}.shiftRight(10));
}

TEST(wingmann_biginteger_modification, shift_right_throw) {
    EXPECT_THROW(
        auto temp = wingmann::numerics::BigInteger{10}.shiftRight(-2),
        std::invalid_argument);
}

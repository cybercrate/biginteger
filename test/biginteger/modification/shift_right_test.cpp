#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_modification, shift_right_1) {
    EXPECT_EQ(
        32,
        wingmann::numerics::biginteger{8192}.shift_right(8));
}

TEST(wingmann_biginteger_modification, shift_right_2) {
    EXPECT_EQ(
        16,
        wingmann::numerics::biginteger{16'384}.shift_right(10));
}

TEST(wingmann_biginteger_modification, shift_right_throw) {
    EXPECT_THROW(
        auto temp = wingmann::numerics::biginteger{10}.shift_right(-2),
        std::invalid_argument);
}

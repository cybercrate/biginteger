#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_modification, shift_left_1) {
    EXPECT_EQ(
        40,
        wingmann::numerics::biginteger{10}.shift_left(2));
}

TEST(wingmann_biginteger_modification, shift_left_shift_2) {
    EXPECT_EQ(
        4096,
        wingmann::numerics::biginteger{512}.shift_left(3));
}

TEST(wingmann_biginteger_modification, shift_left_throw) {
    EXPECT_THROW(
        auto temp = wingmann::numerics::biginteger{10}.shift_left(-2),
        std::invalid_argument);
}

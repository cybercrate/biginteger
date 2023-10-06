#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_constructing, from_char_pointer_assignment_operator) {
    wingmann::numerics::BigInteger number = "2048";
    EXPECT_EQ(number, 2048);
}

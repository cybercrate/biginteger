#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_constructing, from_integral_assignment_operator) {
    alf::num::biginteger number = 2048;
    EXPECT_EQ(number, 2048);
}

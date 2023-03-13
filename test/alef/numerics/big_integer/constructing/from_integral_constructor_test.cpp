#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_constructing, from_integral_constructor) {
    EXPECT_EQ(alf::num::big_integer{2048}, 2048);
}

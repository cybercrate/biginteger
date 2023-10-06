#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_constructing, from_integral_constructor) {
    EXPECT_EQ(wingmann::numerics::BigInteger{2048}, 2048);
}

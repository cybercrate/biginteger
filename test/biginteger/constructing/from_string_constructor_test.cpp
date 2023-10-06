#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_constructing, from_string_constructor) {
    std::string value{"2048"};
    wingmann::numerics::BigInteger number{value};

    EXPECT_EQ(number, 2048);
}

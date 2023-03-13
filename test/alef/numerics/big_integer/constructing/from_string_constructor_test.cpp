#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_constructing, from_string_constructor) {
    std::string value{"2048"};
    alf::num::big_integer number{value};

    EXPECT_EQ(number, 2048);
}

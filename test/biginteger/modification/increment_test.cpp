#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_modification, increment_prefix) {
    wingmann::numerics::BigInteger number{256};
    EXPECT_EQ(257, ++number);
}

TEST(wingmann_biginteger_modification, increment_postfix) {
    wingmann::numerics::BigInteger number{512};

    auto temp = number++;
    auto decremented_value = number;

    EXPECT_EQ(temp, 512);
    EXPECT_EQ(decremented_value, 513);
}

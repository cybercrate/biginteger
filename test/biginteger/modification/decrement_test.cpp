#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_modification, decrement_prefix) {
    wingmann::numerics::biginteger number{256};
    EXPECT_EQ(255, --number);
}

TEST(wingmann_biginteger_modification, decrement_postfix) {
    wingmann::numerics::biginteger number{512};

    auto temp = number--;
    auto decremented_value = number;

    EXPECT_EQ(temp, 512);
    EXPECT_EQ(decremented_value, 511);
}

#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_modification, increment_prefix) {
    alf::num::biginteger number{256};
    EXPECT_EQ(257, ++number);
}

TEST(alef_numerics_biginteger_modification, increment_postfix) {
    alf::num::biginteger number{512};

    auto temp = number++;
    auto decremented_value = number;

    EXPECT_EQ(temp, 512);
    EXPECT_EQ(decremented_value, 513);
}

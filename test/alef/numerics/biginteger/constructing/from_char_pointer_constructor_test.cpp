#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_constructing, from_char_pointer_constructor) {
    EXPECT_EQ(alf::num::biginteger{"2048"}, 2048);
}

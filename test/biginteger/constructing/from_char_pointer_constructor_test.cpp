#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_constructing, from_char_pointer_constructor) {
    EXPECT_EQ(wingmann::numerics::biginteger{"2048"}, 2048);
}

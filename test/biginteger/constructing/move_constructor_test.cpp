#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_constructing, move_constructor) {
    wingmann::numerics::biginteger from{1024};
    wingmann::numerics::biginteger to{std::move(from)};

    EXPECT_NE(from, to);
    EXPECT_EQ(from, 0);
    EXPECT_EQ(to, 1024);
}

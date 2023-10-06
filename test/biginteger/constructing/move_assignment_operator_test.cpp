#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_constructing, move_assignment_operator) {
    wingmann::numerics::BigInteger from{1024};
    wingmann::numerics::BigInteger to = std::move(from);

    EXPECT_NE(from, to);
    EXPECT_EQ(from, 0);
    EXPECT_EQ(to, 1024);
}

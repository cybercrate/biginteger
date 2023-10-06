#include <biginteger/bigInteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_constructing, copy_assignment_operator) {
    wingmann::numerics::BigInteger from{1024};
    wingmann::numerics::BigInteger same = from;

    EXPECT_EQ(from, same);
}

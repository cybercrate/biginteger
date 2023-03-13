#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_constructing, move_assignment_operator) {
    alf::num::big_integer from{1024};
    alf::num::big_integer to = std::move(from);

    EXPECT_NE(from, to);
    EXPECT_EQ(from, 0);
    EXPECT_EQ(to, 1024);
}

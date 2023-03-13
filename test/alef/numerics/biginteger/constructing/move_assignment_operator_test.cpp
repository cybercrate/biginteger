#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_constructing, move_assignment_operator) {
    alf::num::biginteger from{1024};
    alf::num::biginteger to = std::move(from);

    EXPECT_NE(from, to);
    EXPECT_EQ(from, 0);
    EXPECT_EQ(to, 1024);
}

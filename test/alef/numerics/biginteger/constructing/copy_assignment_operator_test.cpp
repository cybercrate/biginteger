#include <alef/numerics/biginteger.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_constructing, copy_assignment_operator) {
    alf::num::biginteger from{1024};
    alf::num::biginteger same = from;

    EXPECT_EQ(from, same);
}

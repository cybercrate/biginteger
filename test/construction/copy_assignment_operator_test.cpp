#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_construction, copy_assignment_operator)
{
    big_integer from{1024};
    big_integer same = from;

    EXPECT_EQ(from, same);
}

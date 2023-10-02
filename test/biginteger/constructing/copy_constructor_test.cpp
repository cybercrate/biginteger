#include <biginteger/biginteger.h>
#include <gtest/gtest.h>

TEST(wingmann_biginteger_constructing, copy_constructor) {
    wingmann::numerics::biginteger from{1024};
    wingmann::numerics::biginteger same{from};

    EXPECT_EQ(from, same);
}

#include <alef/numerics/big_integer.h>

#include <gtest/gtest.h>

TEST(alef_numerics_biginteger_constructing, copy_constructor) {
    alf::num::big_integer from{1024};
    alf::num::big_integer same{from};

    EXPECT_EQ(from, same);
}

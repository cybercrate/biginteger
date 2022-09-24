#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, pow) {
    EXPECT_EQ(big_integer{256}.pow(9), "4722366482869645213696");
}

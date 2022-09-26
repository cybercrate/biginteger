#include "big_integer/big_integer.h"

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(biginteger_arithmetic, operator_divide_pp) {
    EXPECT_EQ(1, big_integer{1024} / 1024);
}

TEST(biginteger_arithmetic, operator_divide_pn) {
    EXPECT_EQ(-1, big_integer{1024} / -1024);
}

TEST(biginteger_arithmetic, operator_divide_np) {
    EXPECT_EQ(-1, big_integer{-1024} / 1024);
}

TEST(biginteger_arithmetic, operator_divide_nn) {
    EXPECT_EQ(1, big_integer{-1024} / -1024);
}

TEST(biginteger_arithmetic, divide_pp_1) {
    EXPECT_EQ(1, big_integer{1024}.divide(1024));
}

TEST(biginteger_arithmetic, divide_pp_2) {
    EXPECT_EQ(1, big_integer::divide(1024, 1024));
}

TEST(biginteger_arithmetic, divide_pn_1) {
    EXPECT_EQ(-1, big_integer{1024}.divide(-1024));
}

TEST(biginteger_arithmetic, divide_pn_2) {
    EXPECT_EQ(-1, big_integer::divide(1024, -1024));
}

TEST(biginteger_arithmetic, divide_np_1) {
    EXPECT_EQ(-1, big_integer{-1024}.divide(1024));
}

TEST(biginteger_arithmetic, divide_np_2) {
    EXPECT_EQ(-1, big_integer::divide(-1024, 1024));
}

TEST(biginteger_arithmetic, divide_nn_1) {
    EXPECT_EQ(1, big_integer{-1024}.divide(-1024));
}

TEST(biginteger_arithmetic, divide_nn_2) {
    EXPECT_EQ(1, big_integer::divide(-1024, -1024));
}

TEST(biginteger_arithmetic, divide_1) {
    big_integer a{"47928462746237462535457589801132323"};
    big_integer b{"72389647642934273643247"};

    EXPECT_EQ(a / b, 662090012962);
}

TEST(biginteger_arithmetic, divide_2) {
    big_integer a =
        "83278678432772049834632746732473264783264732784736674326476732848343264734628374623874326";
    big_integer b = "137297389734304327483946937453742798792429872384727432798427432847737";

    EXPECT_EQ(a / b, "606556895174275286785");
}

TEST(biginteger_arithmetic, divide_negative) {
    big_integer a{"-39328643647846264872638743247324678324"};
    big_integer b{"273049872348732984783274789347973289"};

    EXPECT_EQ(a / b, -144);
}

TEST(biginteger_arithmetic, divide_big_nubers) {
    big_integer a =
        "-83470328946234832472647364371122002023983749864751122912892393782738361273213892738723821"
        "73236263263273128372138218783218973721838712736736748365365783658325319112003282382732747";

    big_integer b =
        "78326478367849234732647832547823547326473269472343212231237214219381438921134128321438112"
        "41389214328123189124389412234";

    EXPECT_EQ(a / b, "-1065671924559511415122777219324972312367557120547789829150597");
}

TEST(biginteger_arithmetic, divide_throw) {
    EXPECT_THROW(big_integer{} / 0, std::invalid_argument);
}
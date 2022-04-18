#include "big_integer.h"

#include "gtest/gtest.h"

using namespace wingmann;

TEST(big_integer, divide_1)
{
    big_integer a{"47928462746237462535457589801132323"};
    big_integer b{"72389647642934273643247"};

    auto actual = (a / b).to_string();
    std::string expected = "662090012962";

    EXPECT_EQ(expected, actual);
}

TEST(big_integer, divide_2)
{
    std::string i =
        "83278678432772049834632746732473264783264732784736674326476732848343264734628374623874326";
    std::string j =
        "137297389734304327483946937453742798792429872384727432798427432847737";

    big_integer a{i};
    big_integer b{j};

    auto actual = (a / b).to_string();
    std::string expected = "606556895174275286785";

    EXPECT_EQ(expected, actual);
}

TEST(big_integer, divide_negative)
{
    big_integer a{"-39328643647846264872638743247324678324"};
    big_integer b{"273049872348732984783274789347973289"};

    auto actual = (a / b).to_string();

    std::string expected = "-144";

    EXPECT_EQ(expected, actual);
}

TEST(big_integer, divide_big_nubers)
{
    std::string i =
        "-83470328946234832472647364371122002023983749864751122912892393782738361273213892738723821"
        "73236263263273128372138218783218973721838712736736748365365783658325319112003282382732747";

    std::string j =
        "78326478367849234732647832547823547326473269472343212231237214219381438921134128321438112"
        "41389214328123189124389412234";

    big_integer a{i};
    big_integer b{j};

    auto actual = (a / b).to_string();
    std::string expected = "-1065671924559511415122777219324972312367557120547789829150597";

    EXPECT_EQ(expected, actual);
}

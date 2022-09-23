#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, multiply_1) {
    big_integer a{"47928462746237462535457589801132323"};
    big_integer b{"723896476429342736432472348234678423648793264764"};

    auto expected =
        "34695245302676318737071175006307707720045893282166198119997687973705978343137366772";

    EXPECT_EQ(a * b, expected);
}

TEST(big_integer, multiply_2) {
    big_integer a =
        "83278678432772049834632746732473264783264732784736674326476732848343264734628374623874326";
    big_integer b = "137297389734304327483946937453742798792429872384727432798427432847737";

    auto expected =
        "114339451693421084348015140812324157171007600613842578548900068836068143180155889217708952"
        "21610409796556693510328684345575828730864876174324430417430181500262";

    EXPECT_EQ(a * b, expected);
}

TEST(big_integer, multiply_negative) {
    big_integer a{"-39328643647846264872638743247324678324"};
    big_integer b{"273049872348732984783274789347973289"};

    auto expected{"-10738681127693230985943313336820847550063005661139320641322082403269287636"};

    EXPECT_EQ(a * b, expected);
}

TEST(big_integer, multiply_big_nubers) {
    big_integer a =
        "-83470328946234832472647364371122002023983749864751122912892393782738361273213892738723821"
        "732362632632731283721382187832189737218387127367367483653657836583253191120032823827327473"
        "743636837567382373248374239910819084143748938483256325767235237823748917127093283982348478"
        "397437657236573265732874329874893274893278935657636";

    big_integer b =
        "-78326478367849234732647832547823547326473269472343212231237214219381438921134128321438112"
        "413892143281231891243894122348124319283418934957387503867634267848281273189281398219381829"
        "392483242394632647678274626420031903288347264632456234632423648237482347893748732647735432"
        "54662747239874981894912841784847863472637842784287432974";

    auto expected =
        "653793691456452241425736528086713653668589904335009594034417256468769590555579252710413588"
        "697840646400690694010583809522250110649000897587874850476028456180552525248294202182958580"
        "492573047785861473618640533932837845445780409005643671558302780955112185098045921735018795"
        "852822562877126343305977256859402735153675097767162786426635068841960655769766125681211997"
        "300505982147696565971117868636793592683925547056042903189412590011379737022421376997209259"
        "463154114158945944628428255639451530390368894626742229332358138721883014155151223536872374"
        "953076509924329098292972708344874153851380401971304185223739211986416223678775823415790114"
        "186252961289464";

    EXPECT_EQ(a * b, expected);
}

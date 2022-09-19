#include <big_integer/big_integer.h>

#include <gtest/gtest.h>

using namespace wingmann::numerics;

TEST(big_integer, add)
{
    big_integer a{"213283396647678464710419826418277230127361770187167317837127838163723763"};
    big_integer b{"903819310371273282019839077556598710691209128309837263716376338084991064"};

    big_integer expected =
        "1117102707018951746730258903974875940818570898497004581553504176248714827";

    EXPECT_EQ(a + b, expected);
}

TEST(big_integer, add_negative_1)
{
    big_integer a{"2132833966476784647104198264182772301273617701871673178"};
    big_integer b{"-7106912091283098372637163763380849910641"};

    big_integer expected = {"2132833966476777540192106981084399664109854321021762537"};

    EXPECT_EQ(a + b, expected);
}

TEST(big_integer, add_negative_2)
{
    big_integer a{"-7837893232"};
    big_integer b{"-832721963128309837"};

    EXPECT_EQ(a + b, big_integer{"-832721970966203069"});
}

TEST(big_integer, add_big_numbers)
{
    big_integer a =
        "461848481646846848464811468486464282146814684841848648648484894484842982419848949889294189"
        "164842894898919849892884289289489891489482819848949824298439849849788123892498438948348384"
        "879884198128489484389494294894849800391371301984646146141896481640804601419458667398173872"
        "897479079824602840607267463246034786786478283748764862378487268432746238704234627846189113"
        "89729837972371738129837239818237712839173872389712893712893891238712387128931273317907293";

    big_integer b =
        "901731983182639861263921636237612767141715861517184984984982894989819846021487199798897427"
        "384728341894689641289463621486238641889268964892368496238468293684621384629426982526598165"
        "983269818235631658295821983217312893748278926441842893842984518942989498432449741989882848"
        "748920484724891419824298498418419842928984983249849841981498298419848949828189489498498228"
        "24984149829849848981994284894198492498419849849214942984984198984924720484962642647732462";

    big_integer expected =
        "136358046482948670972873310472407704928853054635903363363346778947466282844133614968819161"
        "654957123679360949118234791077572853337875178474131832053690814353440950852192542147494655"
        "086315401636412114268531627811216269413965022842648903998488100058379409985190840938805672"
        "164639956454949426043156596166445462971546326699861470435998556685259518853242411734468734"
        "21471398780222158711183152471243620533759372223892783669787809022363710761389391596563"
        "9755";

    EXPECT_EQ(a + b, expected);
}

#include <gtest/gtest.h>
#include "rule.h"

using ::testing::ExitedWithCode;

static void ExpectMaskBits(uint16_t mask, std::initializer_list<int> ones, std::initializer_list<int> zeros) {
    for (int b : ones)   EXPECT_TRUE((mask >> b) & 1u);
    for (int b : zeros)  EXPECT_FALSE((mask >> b) & 1u);
}

TEST(RuleTest, ClassicLife_B3S23) {
    Rule r("B3/S23");

    auto b = r.GetBirthMask();
    auto s = r.GetSurviveMask();
    ExpectMaskBits(b, {3}, {0,1,2,4,5,6,7,8});
    ExpectMaskBits(s, {2,3}, {0,1,4,5,6,7,8});

    for (int n = 0; n <= 8; ++n) {
        uint8_t born = r.decide(n, 0);
        EXPECT_EQ(born, n == 3 ? 1 : 0);
        uint8_t survive = r.decide(n, 1);
        EXPECT_EQ(survive, (n == 2 || n == 3) ? 1 : 0);
    }

    EXPECT_EQ(r.getRule(), "#R B3/S23");
}

TEST(RuleTest, ParseWithSpaces) {
    Rule r("   #  R   B135 / S  02468  ");
    auto b = r.GetBirthMask();
    auto s = r.GetSurviveMask();
    ExpectMaskBits(b, {1,3,5}, {0,2,4,6,7,8});
    ExpectMaskBits(s, {0,2,4,6,8}, {1,3,5,7});
    EXPECT_EQ(r.getRule(), "#R B135/S02468");
}

TEST(RuleTest, LoadRuleOverwritesPrevious) {
    Rule r("B3/S23");
    r.loadRule("B12/S8");
    auto b = r.GetBirthMask();
    auto s = r.GetSurviveMask();
    ExpectMaskBits(b, {1,2}, {0,3,4,5,6,7,8});
    ExpectMaskBits(s, {8}, {0,1,2,3,4,5,6,7});
    EXPECT_EQ(r.getRule(), "#R B12/S8");
}

TEST(RuleDeathTest, MissingSectionsDies) {
    EXPECT_EXIT({ Rule r("B3"); }, ExitedWithCode(1), "both B and S sections are required");
    EXPECT_EXIT({ Rule r("S23"); }, ExitedWithCode(1), "both B and S sections are required");
}

TEST(RuleDeathTest, DigitBeforeSectionDies) {
    EXPECT_EXIT({ Rule r("3/S23"); }, ExitedWithCode(1), "digit before B/S section");
}

TEST(RuleDeathTest, UnexpectedCharacterDies) {
    EXPECT_EXIT({ Rule r("B3/S2x"); }, ExitedWithCode(1), "unexpected character");
}

TEST(RuleDeathTest, DuplicateDigitDies) {
    EXPECT_EXIT({ Rule r("B33/S23"); }, ExitedWithCode(1), "duplicate digit in B");
    EXPECT_EXIT({ Rule r("B3/S223"); }, ExitedWithCode(1), "duplicate digit in S");
}

TEST(RuleTest, FullRangeDigitsAllowed) {
    Rule r("B012345678/S012345678");
    auto b = r.GetBirthMask();
    auto s = r.GetSurviveMask();
    ExpectMaskBits(b, {0,1,2,3,4,5,6,7,8}, {});
    ExpectMaskBits(s, {0,1,2,3,4,5,6,7,8}, {});
    EXPECT_EQ(r.decide(0, 0), 1);
    EXPECT_EQ(r.decide(8, 1), 1);
}
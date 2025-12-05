#include <gtest/gtest.h>
#include "rule.h"

TEST(RuleTest, LoadCustomRuleString) {
    Rule r;
    r.loadRule("#R B36/S23");
    EXPECT_EQ(r.getRule(), "#R B36/S23");
}

TEST(RuleTest, Decide) {
    Rule r;
    r.loadRule("#R B36/S23");

    EXPECT_EQ(r.decide(3, 0), 1);
    EXPECT_EQ(r.decide(2, 1), 1);
    EXPECT_EQ(r.decide(3, 1), 1);
    EXPECT_EQ(r.decide(1, 1), 0);
}
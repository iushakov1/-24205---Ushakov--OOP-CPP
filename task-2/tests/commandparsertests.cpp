//
// Created by ioanushakov on 05.12.2025.
//

#include <gtest/gtest.h>
#include "commandparser.h"
#include "command.h"

TEST(CommandParserTest, ParseTickNoArgGivesOneStep) {
    CommandParser p;
    std::string input = "tick";
    auto cmd = p.parseCommand(input);
    auto tick = ((TickCommand*)cmd)->getNumOfTicks();
    EXPECT_EQ(1, tick);
}

TEST(CommandParserTest, ParseTickWithNumber) {
    CommandParser p;
    std::string input = "tick 10";
    auto cmd = p.parseCommand(input);
    auto tick = ((TickCommand*)cmd)->getNumOfTicks();
    EXPECT_EQ(10, tick);
}

TEST(CommandParserTest, ParsesExitCommand) {
    CommandParser p;
    std::string s = "exit";
    Command* cmd = p.parseCommand(s);
    auto* exitCmd = (ExitCommand*)cmd;
    EXPECT_NE(exitCmd, nullptr);
}

TEST(CommandParserTest, ParsesDumpWithPath) {
    CommandParser p;
    std::string s = "dump out.life";
    Command* cmd = p.parseCommand(s);
    auto* dumpCmd = (ExitCommand*)(cmd);
    EXPECT_NE(dumpCmd, nullptr);
}
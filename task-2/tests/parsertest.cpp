#include "parser.h"

#include <gtest/gtest.h>

static char* cstr(const char* s) { return const_cast<char*>(s); }

TEST(ParserArgvTest, Mode3_LongFlags_AllValid) {
    int argc = 4;
    char* argv[] = {
            cstr("task_2"),
            cstr("--input=testInput.life"),
            cstr("--iterations=10"),
            cstr("--output=testOutput.life")
    };
    auto parsed = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<Options>(parsed));
    const Options& opt = std::get<Options>(parsed);
    EXPECT_EQ(opt.mode, 3);
    EXPECT_EQ(opt.inputPath, "testInput.life");
    EXPECT_EQ(opt.outputPath, "testOutput.life");
    EXPECT_EQ(opt.iteration, 10);
}

TEST(ParserArgvTest, Mode3_ShortFlags_AllValid) {
    int argc = 6;
    char* argv[] = {
            cstr("task_2"),
            cstr("--input=testInput.life"),
            cstr("-i"),
            cstr("7"),
            cstr("-o"),
            cstr("out.life")
    };
    auto parsed = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<Options>(parsed));
    const Options& opt = std::get<Options>(parsed);
    EXPECT_EQ(opt.mode, 3);
    EXPECT_EQ(opt.inputPath, "testInput.life");
    EXPECT_EQ(opt.outputPath, "out.life");
    EXPECT_EQ(opt.iteration, 7);
}

TEST(ParserArgvTest, Mode3_MissingIterations_Invalid) {
    int argc = 3;
    char* argv[] = {
            cstr("task_2"),
            cstr("--input=testInput.life"),
            cstr("--output=out.life")
    };
    auto parsed = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<ParseError>(parsed));
    EXPECT_NE(std::get<ParseError>(parsed).message.find("unexpected"), std::string::npos);
}

TEST(ParserArgvTest, Mode3_InvalidIterationsKey) {
    int argc = 4;
    char* argv[] = {
            cstr("task_2"),
            cstr("--input=testInput.life"),
            cstr("--iter=10"),
            cstr("--output=out.life")
    };
    auto parsed = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<ParseError>(parsed));
    EXPECT_NE(std::get<ParseError>(parsed).message.find("iterations"), std::string::npos);
}

TEST(ParserArgvTest, Mode3_ShortI_ButNotEnoughArgs) {
    int argc = 4;
    char* argv[] = {
            cstr("task_2"),
            cstr("--input=testInput.life"),
            cstr("-i"),
            cstr("10")
    };
    auto parsed = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<ParseError>(parsed));
    EXPECT_NE(std::get<ParseError>(parsed).message.find("not enough arguments"), std::string::npos);
}

TEST(ParserArgvTest, Mode3_ShortO_ButNotEnoughArgs) {
    int argc = 5;
    char* argv[] = {
            cstr("task_2"),
            cstr("--input=testInput.life"),
            cstr("-i"),
            cstr("10"),
            cstr("-o")
    };
    auto parsed = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<ParseError>(parsed));
    EXPECT_NE(std::get<ParseError>(parsed).message.find("not enough arguments"), std::string::npos);
}

TEST(ParserArgvTest, Mode3_InvalidOutputKey) {
    int argc = 4;
    char* argv[] = {
            cstr("task_2"),
            cstr("--input=testInput.life"),
            cstr("--iterations=5"),
            cstr("--out=out.life")
    };
    auto parsed = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<ParseError>(parsed));
    EXPECT_NE(std::get<ParseError>(parsed).message.find("output"), std::string::npos);
}

TEST(ParserArgvTest, Mode2_OnlyInputPath) {
    int argc = 2;
    char* argv[] = {
            cstr("task_2"),
            cstr("input_dir_or_file")
    };
    auto parsed = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<Options>(parsed));
    const Options& opt = std::get<Options>(parsed);
    EXPECT_EQ(opt.mode, 2);
    EXPECT_EQ(opt.inputPath, "input_dir_or_file");
}

TEST(ParserArgvTest, Mode1_NoArgs) {
    int argc = 1;
    char* argv[] = { cstr("task_2") };
    auto parsed = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<Options>(parsed));
    const Options& opt = std::get<Options>(parsed);
    EXPECT_EQ(opt.mode, 1);
}

TEST(ParserArgvTest, UnexpectedMode_Error) {
    int argc = 3;
    char* argv[] = { cstr("task_2"), cstr("--foo"), cstr("--bar") };
    auto parsed = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<ParseError>(parsed));
    EXPECT_NE(std::get<ParseError>(parsed).message.find("unexpected"), std::string::npos);
}

TEST(ParserCommandTest, ExitCommand) {
    std::string s = "exit";
    auto v = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(v));
    const Command& cmd = std::get<Command>(v);
    EXPECT_EQ(cmd.name, "exit");
}

TEST(ParserCommandTest, HelpCommand) {
    std::string s = "help";
    auto v = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(v));
    EXPECT_EQ(std::get<Command>(v).name, "help");
}

TEST(ParserCommandTest, DumpWithoutArg_Error) {
    std::string s = "dump";
    auto v = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<ParseError>(v));
    EXPECT_NE(std::get<ParseError>(v).message.find("dump"), std::string::npos);
}

TEST(ParserCommandTest, DumpWithPath) {
    std::string s = "dump file.life";
    auto v = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(v));
    const Command& cmd = std::get<Command>(v);
    EXPECT_EQ(cmd.name, "dump");
    EXPECT_EQ(cmd.args, "file.life");
}

TEST(ParserCommandTest, TickDefault1) {
    std::string s = "t";
    auto v = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(v));
    const Command& cmd = std::get<Command>(v);
    EXPECT_EQ(cmd.name, "tick");
    EXPECT_EQ(cmd.digitParam, 1);
}

TEST(ParserCommandTest, TickAliasTick) {
    std::string s = "tick";
    auto v = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(v));
    EXPECT_EQ(std::get<Command>(v).name, "tick");
    EXPECT_EQ(std::get<Command>(v).digitParam, 1);
}

TEST(ParserCommandTest, TickWithNumber) {
    std::string s = "tick 5";
    auto v = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(v));
    const Command& cmd = std::get<Command>(v);
    EXPECT_EQ(cmd.name, "tick");
    EXPECT_EQ(cmd.digitParam, 5);
}

TEST(ParserCommandTest, UnknownCommand_Error) {
    std::string s = "foobar";
    auto v = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<ParseError>(v));
    EXPECT_NE(std::get<ParseError>(v).message.find("no such command"), std::string::npos);
}
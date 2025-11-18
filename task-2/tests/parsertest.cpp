#include "parser.h"

#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <unistd.h>

TEST(ParseCommandTest, ExitNoArgs) {
    std::string s = "exit";
    auto res = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(res));
    const Command& c = std::get<Command>(res);
    EXPECT_EQ(c.name, "exit");
    EXPECT_EQ(c.args, "");
}

TEST(ParseCommandTest, DumpWithPath) {
    std::string s = "dump out.life";
    auto res = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(res));
    const Command& c = std::get<Command>(res);
    EXPECT_EQ(c.name, "dump");
    EXPECT_EQ(c.args, "out.life");
}

TEST(ParseCommandTest, TickAliasTDefault1) {
    std::string s = "t";
    auto res = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(res));
    const Command& c = std::get<Command>(res);
    EXPECT_EQ(c.name, "tick");
    EXPECT_EQ(c.digitParam, 1);
}

TEST(ParseCommandTest, TickWordDefault1) {
    std::string s = "tick";
    auto res = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(res));
    const Command& c = std::get<Command>(res);
    EXPECT_EQ(c.name, "tick");
    EXPECT_EQ(c.digitParam, 1);
}

TEST(ParseCommandTest, TickWithNumber) {
    std::string s = "tick 15";
    auto res = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(res));
    const Command& c = std::get<Command>(res);
    EXPECT_EQ(c.name, "tick");
    EXPECT_EQ(c.digitParam, 15);
}

TEST(ParseCommandTest, HelpNoArgs) {
    std::string s = "help";
    auto res = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<Command>(res));
    const Command& c = std::get<Command>(res);
    EXPECT_EQ(c.name, "help");
}

TEST(ParseCommandTest, DumpMissingPathError) {
    std::string s = "dump";
    auto res = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<ParseError>(res));
    const ParseError& e = std::get<ParseError>(res);
    EXPECT_EQ(e.message, "dump without file's path\n");
}

TEST(ParseCommandTest, UnknownCommandError) {
    std::string s = "foobar 123";
    auto res = Parser::parseCommand(s);
    ASSERT_TRUE(std::holds_alternative<ParseError>(res));
    const ParseError& e = std::get<ParseError>(res);
    EXPECT_EQ(e.message, "unknown command");
}

static std::string makeTempFile(const char* prefix) {
    char tmpl[256];
    std::snprintf(tmpl, sizeof(tmpl), "/tmp/%sXXXXXX", prefix);
    int fd = mkstemp(tmpl);
    if (fd != -1) close(fd);
    return std::string(tmpl);
}

TEST(ParseArgvTest, Mode1NoArgs) {
    int argc = 1;
    char* argv[] = { (char*)"prog" };
    auto res = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<Options>(res));
    const Options& opt = std::get<Options>(res);
    EXPECT_EQ(opt.mode, 1);
}

TEST(ParseArgvTest, Mode2InputOnlyValid) {
    auto in = makeTempFile("in_");
    std::ofstream f(in);
    f << "x";
    int argc = 2;
    char* argv[] = { (char*)"prog", (char*)in.c_str() };
    auto res = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<Options>(res));
    const Options& opt = std::get<Options>(res);
    EXPECT_EQ(opt.mode, 2);
    EXPECT_EQ(opt.inputPath, in);
}

TEST(ParseArgvTest, Mode2InputOnlyInvalidPathError) {
    int argc = 2;
    char* argv[] = { (char*)"prog", (char*)"no_such_file.life" };
    auto res = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<ParseError>(res));
    const ParseError& e = std::get<ParseError>(res);
    EXPECT_EQ(e.message, "invalid file's path");
}

TEST(ParseArgvTest, Mode3AllValid) {
    auto in = makeTempFile("in_");
    auto out = makeTempFile("out_");
    std::ofstream f(in);
    f << "x";
    std::ofstream g(out);
    g << "";
    int argc = 4;
    char* argv[] = {
            (char*)"prog",
            (char*)in.c_str(),
            (char*)"10",
            (char*)out.c_str()
    };
    auto res = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<Options>(res));
    const Options& opt = std::get<Options>(res);
    EXPECT_EQ(opt.mode, 3);
    EXPECT_EQ(opt.inputPath, in);
    EXPECT_EQ(opt.iteration, 10);
    EXPECT_EQ(opt.outputPath, out);
}

TEST(ParseArgvTest, Mode3BadInputPathError) {
    auto out = makeTempFile("out_");
    std::ofstream g(out);
    g << "";
    int argc = 4;
    char* argv[] = { (char*)"prog", (char*)"no_file.life",  (char*)"5", (char*)out.c_str() };
    auto res = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<ParseError>(res));
    const ParseError& e = std::get<ParseError>(res);
    EXPECT_EQ(e.message, "first argument is not a correct input file path");
}

TEST(ParseArgvTest, Mode3BadIterationNumberError) {
    auto in = makeTempFile("in_");
    auto out = makeTempFile("out_");
    { std::ofstream(in) << "x"; std::ofstream(out) << ""; }
    int argc = 4;
    char* argv[] = { (char*)"prog", (char*)in.c_str(), (char*)"10a", (char*)out.c_str() };
    auto res = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<ParseError>(res));
    const ParseError& e = std::get<ParseError>(res);
    EXPECT_EQ(e.message, "second argument is not a correct iterations number");
}

TEST(ParseArgvTest, Mode3BadOutputPath_Error) {
    auto in = makeTempFile("in_");
    { std::ofstream(in) << "x"; }
    int argc = 4;
    char* argv[] = { (char*)"prog", (char*)in.c_str(),  (char*)"7", (char*)"__cannot_open__/file" };
    auto res = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<ParseError>(res));
    const ParseError& e = std::get<ParseError>(res);
    EXPECT_EQ(e.message, "third argument is not a correct output path");
}

TEST(ParseArgvTest, UnexpectedModeErrorMessage) {
    int argc = 3;
    char* argv[] = { (char*)"prog", (char*)"one", (char*)"two" };
    auto res = Parser::parseArgv(argc, argv);
    ASSERT_TRUE(std::holds_alternative<ParseError>(res));
    const ParseError& e = std::get<ParseError>(res);
    EXPECT_NE(e.message.find("unexpected mode."), std::string::npos);
}


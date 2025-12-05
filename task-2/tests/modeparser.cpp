//
// Created by ioanushakov on 05.12.2025.
//

#include "modeparser.h"
#include "mode.h"

#include <gtest/gtest.h>
#include <fstream>

namespace fs = std::filesystem;

TEST(ModeParserTest, FileModeWhenValidPath) {
    std::string inputFile = "testInput.life";
    std::ofstream out(inputFile);
    out << "#Life 1.06\n";
    out.close();

    ModeParser parser;
    const char* argv[] = {"prog", inputFile.c_str()};
    Mode* mode = parser.parseMode(2, (char**)argv);

    auto* fileMode = (FileMode*)(mode);
    EXPECT_NE(fileMode, nullptr);

}

TEST(ModeParserTest, ErrorModeWhenInvalidPath) {
    testing::internal::CaptureStderr();
    ModeParser parser;

    const char* argv[] = {"prog", "definitely_no_such_file_123.life"};
    Mode* mode = parser.parseMode(2, (char**)argv);

    std::string output = testing::internal::GetCapturedStderr();
    auto* errorMode = (ErrorMode*)mode;
    EXPECT_NE(errorMode, nullptr);
    EXPECT_EQ("mode parser: invalid file's path\n", output);

}

TEST(ModeParserTest, OfflineModeWhenFourArgs) {
    std::string inputFile = "testInput.life";
    std::string outputFile = "testOutput.life";

    std::ofstream out(inputFile);
    out << "#Life 1.06\n";
    out << "#N TEST\n";
    out << "#R B1357/S1357\n";
    out << "50 50\n"
           "14 10\n"
           "15 10";
    out.close();
    ModeParser parser;
    std::string ticks = "3";

    const char* argvC[] = {
            "prog",
            inputFile.c_str(),
            ticks.c_str(),
            outputFile.c_str()
    };
    Mode* mode = parser.parseMode(4, (char**)(argvC));
    mode->start();

    auto* offlineMode = (OfflineMode*)mode;
    EXPECT_NE(offlineMode, nullptr);

}
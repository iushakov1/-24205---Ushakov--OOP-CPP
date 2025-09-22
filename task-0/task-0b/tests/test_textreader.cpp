#include "../src/textreader.h"

#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>

TEST(TextReaderTest, SimpleTest) {
    std::string filename = "test_input.txt";

    std::ofstream testFile(filename);
    testFile << "line1\nline2\n";
    testFile.close();

    TextReader reader(filename);
    auto lines = reader.readLines();

    ASSERT_EQ(lines.size(), 2);
    EXPECT_EQ(lines.front(), "line1");
    EXPECT_EQ(lines.back(), "line2");

    std::remove(filename.c_str());
}

TEST(TextReaderTest, EmptyFile){
    std::string filename = "test_input.txt";

    std::ofstream testFile(filename);
    testFile << "";
    testFile.close();

    TextReader reader(filename);
    auto lines = reader.readLines();

    ASSERT_EQ(lines.size(), 0);
}

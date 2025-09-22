#include "../src/resultwriter.h"

#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <list>
#include <string>

TEST(ResultWriterTest, WritesCorrectOutput) {
    std::string filename = "test_output.txt";

    std::map<std::string, int> counts = {{"hello", 2}, {"world", 1}};
    int totalWords = 3;

    ResultWriter writer(filename);
    writer.write(counts, totalWords);

    std::ifstream in(filename);
    ASSERT_TRUE(in.is_open());

    std::string line;
    std::getline(in, line);

    EXPECT_NE(line.find("hello"), std::string::npos);
    EXPECT_NE(line.find("66.6"), std::string::npos); // 2 из 3 = 66.6%

    std::getline(in, line);
    EXPECT_NE(line.find("world"), std::string::npos);
    EXPECT_NE(line.find("33.3"), std::string::npos); // 1 из 3 = 33.3%

    in.close();
    std::remove(filename.c_str());
}

TEST(ResultWriterTest, EmptyWordCount) {
    std::string filename = "empty_output.txt";
    std::map<std::string, int> counts;
    int totalWords = 0;

    ResultWriter writer(filename);
    writer.write(counts, totalWords);

    std::ifstream in(filename);
    ASSERT_TRUE(in.is_open());

    std::string line;
    EXPECT_FALSE(std::getline(in, line));

    in.close();
    std::remove(filename.c_str());
}
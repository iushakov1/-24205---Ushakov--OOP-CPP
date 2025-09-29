#include "../src/filereader.h"

#include <vector>
#include <gtest/gtest.h>

TEST(fileReaderTest, SimpleFile){
    std::ofstream testInput;
    testInput.open("testInput.txt");
    std::string line1 = "Fear not. Because, i'm with you\n";
    std::string line2 = "Stop the Asriel's plans";
    std::vector<std::string> expVec1 = {"Fear", "not", "Because", "i'm", "with", "you"};
    std::vector<std::string> expVec2 = {"Stop", "the", "Asriel's", "plans"};
    testInput << line1 << line2 << std::endl;

    FileReader reader("testInput.txt");
    std::vector<std::string> splittedLine = reader.getSplittedLine();
    int i = 0;
    for(const auto& word: splittedLine){
        EXPECT_EQ(expVec1[i], word);
        ++i;
    }
    i = 0;
    splittedLine = reader.getSplittedLine();
    for(const auto& word: splittedLine){
        EXPECT_EQ(expVec2[i], word);
        ++i;
    }
}

TEST(fileReaderTest, EmptyFile){
    std::ofstream testInput;
    testInput.open("testInput.txt");
    std::string line1 = " ";
    testInput << line1 << std::endl;

    FileReader reader("testInput.txt");
    std::vector<std::string> splittedLine = reader.getSplittedLine();
    EXPECT_EQ(0, splittedLine.size());
}

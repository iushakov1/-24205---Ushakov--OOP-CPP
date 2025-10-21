#include "../src/splitter.h"

#include <fstream>
#include <vector>
#include <gtest/gtest.h>

TEST(LineSplitterTest, SimpleFile){
    std::string line1 = "Fear not. Because, i'm with you";
    std::string line2 = "For all and beyond";

    std::vector<std::string> expVec = {"Fear", "not", "Because", "i'm", "with", "you", "For", "all", "and", "beyond"};

    Splitter splitter;
    std::vector<std::string> allWords;
    auto newWords1 = splitter.split(line1);
    allWords.insert(allWords.begin(), newWords1.begin(), newWords1.end());
    auto newWords2 = splitter.split(line2);
    allWords.insert(allWords.end(), newWords2.begin(), newWords2.end());

    int i = 0;
    for(const auto& word: allWords){
        EXPECT_EQ(expVec[i], word);
        ++i;
    }

}

TEST(LineSplitterTest, EmptyFile){

    std::string line1 = " ";

    Splitter splitter;
    auto allWords = splitter.split(line1);

    EXPECT_EQ(0, allWords.size());
}

#include "../src/wordcounter.h"

#include <gtest/gtest.h>
#include <list>

TEST(WordCounterTest, CountWordsCorrectly){
    WordCounter wc;
    std::list<std::string> lines = {"hello world", "hello"};
    wc.processLines(lines);
    auto counts = wc.getWordCounter();
    EXPECT_EQ(wc.getTotalWords(), 3);
    EXPECT_EQ(counts["hello"], 2);
    EXPECT_EQ(counts["world"], 1);
}

TEST(WordCounterTest, EmptyInput){
    WordCounter wc;
    std::list<std::string> lines = {};

    wc.processLines(lines);

    auto counts = wc.getWordCounter();
    EXPECT_TRUE(counts.empty());
    EXPECT_EQ(wc.getTotalWords(), 0);
}

TEST(WordCounterTest, MultipleSpacesAndEmptyWords) {
    WordCounter wc;
    std::list<std::string> lines = {"   spaced   out   "};

    wc.processLines(lines);

    auto counts = wc.getWordCounter();
    EXPECT_EQ(wc.getTotalWords(), 2);
    EXPECT_EQ(counts.at("spaced"), 1);
    EXPECT_EQ(counts.at("out"), 1);
}
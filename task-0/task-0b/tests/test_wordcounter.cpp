#include "../src/wordcounter.h"

#include <gtest/gtest.h>
#include <vector>

TEST(wordCounterTest, SimpleLine){
    std::vector<std::string> testVec = {"Fear", "not", "Because", "i'm", "with", "you"};

    WordCounter counter;
    counter.countWords(testVec);

    std::string matchWord = " ";
    for(auto el: counter.getWordCount()){
        for(const auto& word: testVec){
            if(word == std::get<0>(el)){
                matchWord = word;
            }
        }
        EXPECT_EQ(std::get<0>(el), matchWord);
        matchWord = " ";
        EXPECT_EQ(1, std::get<1>(el));
    }
}

TEST(wordCounterTest, EmptyLine){
    std::vector<std::string> testVec = {};
    WordCounter counter;
    counter.countWords(testVec);
    EXPECT_EQ(0, counter.getWordCount().size());
}
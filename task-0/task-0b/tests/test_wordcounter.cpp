#include "../src/wordcounter.h"
#include "../src/filereader.h"

#include <gtest/gtest.h>
#include <vector>

TEST(wordCounterTest, SimpleLine){
    std::string line = "Fear not. Because, i'm with you";
    std::ofstream testInput;
    testInput.open("testInput.txt");
    testInput << line << std::endl;

    FileReader reader("testInput.txt");
    WordCounter counter;
    auto words = reader.getSplittedLine();
    counter.countWords(words);
    std::string matchWord = " ";
    for(auto el: counter.getWordCount()){
        for(const auto& word: words){
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
    std::string line = " ";
    std::ofstream testInput;
    testInput.open("testInput.txt");
    testInput << line << std::endl;

    FileReader reader("testInput.txt");
    WordCounter counter;
    auto words = reader.getSplittedLine();
    counter.countWords(words);
    EXPECT_EQ(0, counter.getWordCount().size());
}
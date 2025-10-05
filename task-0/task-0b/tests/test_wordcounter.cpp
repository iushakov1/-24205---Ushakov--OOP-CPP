#include "../src/filereader.h"
#include "../src/linesplitter.h"
#include "../src/wordcounter.h"

#include <gtest/gtest.h>
#include <vector>

TEST(wordCounterTest, SimpleLine){
    std::string line = "Fear not. Because, i'm with you";
    std::ofstream test_input;
    test_input.open("test_input.txt");
    test_input << line << std::endl;

    FileReader reader("test_input.txt");
    WordCounter counter;
    Linesplitter splitter;
    splitter.splitLine(reader.next());

    auto words = splitter.getWords();
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
    std::ofstream test_input;
    test_input.open("test_input.txt");
    test_input << line << std::endl;

    FileReader reader("test_input.txt");
    WordCounter counter;
    Linesplitter splitter;
    splitter.splitLine(reader.next());

    auto words = splitter.getWords();
    counter.countWords(words);
    EXPECT_EQ(0, counter.getWordCount().size());
}
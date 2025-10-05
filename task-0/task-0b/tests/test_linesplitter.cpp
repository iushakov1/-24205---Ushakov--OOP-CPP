#include "../src/filereader.h"
#include "../src/linesplitter.h"

#include <vector>
#include <gtest/gtest.h>

TEST(LineSplitterTest, SimpleFile){
    std::ofstream test_input;
    test_input.open("test_input.txt");
    std::string line1 = "Fear not. Because, i'm with you\n";
    std::vector<std::string> expVec1 = {"Fear", "not", "Because", "i'm", "with", "you"};
    test_input << line1 << std::endl;

    Linesplitter splitter;
    FileReader reader("test_input.txt");
    splitter.splitLine(reader.next());
    splitter.splitLine(reader.next());

    int i = 0;
    for(const auto& word: splitter.getWords()){
        EXPECT_EQ(expVec1[i], word);
        ++i;
    }

}

TEST(LineSplitterTest, EmptyFile){
    std::ofstream test_input;
    test_input.open("test_input.txt");
    std::string line1 = " ";
    test_input << line1 << std::endl;

    Linesplitter splitter;
    FileReader reader("test_input.txt");
    splitter.splitLine(reader.next());
    EXPECT_EQ(0, splitter.getWords().size());
}

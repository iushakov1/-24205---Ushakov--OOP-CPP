#include "../src/filereader.h"

#include <fstream>
#include <vector>
#include <gtest/gtest.h>

TEST(FileReaderTest, SimpleTest){
    std::ofstream test_input;
    test_input.open("test_input.txt");
    test_input << "hopes and dreams" << std::endl;
    test_input.close();

    FileReader reader("test_input.txt");
    std::string line = reader.next();
    EXPECT_EQ(line, "hopes and dreams");
    reader.close();
}

TEST(FileReaderTest, EmptyFile){
    std::ofstream test_input;
    test_input.open("test_input.txt");
    test_input << "" << std::endl;
    test_input.close();

    FileReader reader("test_input.txt");
    std::string line = reader.next();
    EXPECT_EQ(line, "");
    reader.close();
}
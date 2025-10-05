#include "../src/csvwriter.h"

#include <fstream>
#include <vector>
#include <gtest/gtest.h>

TEST(CSVWriterTest, SimpleVec){
    std::vector<std::string> vec = {"Snake Eater"};

    CSVWriter writer("test_output.txt");
    writer.write(vec);

    std::ifstream testOutput;
    testOutput.open("test_output.txt");

    std::string line;
    std::getline(testOutput, line);
    EXPECT_EQ("Snake Eater", line);
}

TEST(CSVWriterTest, EmptyVec){
    std::vector<std::string> vec = {};

    CSVWriter writer("test_output.txt");
    writer.write(vec);

    std::ifstream testOutput;
    testOutput.open("test_output.txt");

    std::string line;
    std::getline(testOutput, line);
    EXPECT_EQ("", line);
}
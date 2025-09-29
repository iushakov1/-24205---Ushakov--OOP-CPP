#include "../src/csvwriter.h"

#include <fstream>
#include <vector>
#include <gtest/gtest.h>

TEST(CSVWriterTest, SimpleVec){
    std::vector<std::tuple<std::string, int, double>> vec = {{"Snake", 52, 32.1243}};

    CSVWriter writer("test_output.txt");
    writer.writeVector(vec);

    std::ifstream testOutput;
    testOutput.open("test_output.txt");

    std::string line;
    std::getline(testOutput, line);
    EXPECT_EQ("Snake 52 32.1243", line);
}

TEST(CSVWriterTest, EmptyVec){
    std::vector<std::tuple<std::string, int, double>> vec = {};

    CSVWriter writer("test_output.txt");
    writer.writeVector(vec);

    std::ifstream testOutput;
    testOutput.open("test_output.txt");

    std::string line;
    std::getline(testOutput, line);
    EXPECT_EQ("", line);
}
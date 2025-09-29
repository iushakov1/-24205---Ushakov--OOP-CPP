#pragma once

#include <fstream>
#include <string>
#include <vector>

class FileReader {
public:
    explicit FileReader(std::string filename);
    std::vector<std::string> getSplittedLine();
private:
    std::string filename;
    std::ifstream input;
};


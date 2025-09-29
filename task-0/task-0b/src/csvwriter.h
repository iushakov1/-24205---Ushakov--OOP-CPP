#pragma once

#include <fstream>
#include <string>
#include <vector>

class CSVWriter {
public:
    explicit CSVWriter(std::string  filename);
    void writeVector(const std::vector<std::tuple<std::string, int, double>>& vec);
private:
    std::string filename;
    std::ofstream output;
};


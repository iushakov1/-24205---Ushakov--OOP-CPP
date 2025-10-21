#pragma once

#include <fstream>
#include <string>
#include <vector>

class CSVWriter {
public:
    explicit CSVWriter(std::string  filename);
    void open();
    void close();
    void reset();
    void write(const std::vector<std::string>&);
private:
    std::string filename;
    std::ofstream file;
};


#pragma once
#include <map>
#include <string>

class ResultWriter{
public:
    explicit ResultWriter(std::string filename);
    void write(const std::map<std::string, int>& wordCount, int totalWords);
private:
    std::string filename;
};
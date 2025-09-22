#pragma once
#include <list>
#include <string>

class TextReader{
public:
    explicit TextReader(std::string  filename);
    std::list<std::string> readLines();
private:
    std::string filename;
};


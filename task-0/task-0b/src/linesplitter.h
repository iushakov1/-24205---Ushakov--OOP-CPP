#pragma once

#include <string>
#include <vector>

class  Linesplitter {
public:
    void splitLine(const std::string&);
    void resetWords();
    std::vector<std::string> getWords();
private:
    std::vector<std::string> words;
};


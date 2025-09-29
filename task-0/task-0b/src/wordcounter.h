#pragma once

#include <fstream>
#include <map>
#include <string>
#include <vector>

class WordCounter{
public:
    void countWords(const std::vector<std::string>& words);
    std::vector<std::tuple<std::string, int, double>> getWordCount();
private:
    std::map<std::string, int> wordsStat;
    int totalWords = 0;
};
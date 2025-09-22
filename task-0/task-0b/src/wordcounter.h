#pragma once
#include <list>
#include <map>
#include <string>

class WordCounter{
public:
    void processLines(const std::list<std::string>& lines);
    std::map<std::string, int> getWordCounter();
    int getTotalWords() const;
private:
    std::map<std::string, int> wordCount;
    int totalWords = 0;
};

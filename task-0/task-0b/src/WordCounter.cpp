#include "WordCounter.h"

#include <list>
#include <map>
#include <string>
void WordCounter::processLines(const std::list<std::string>& lines){
    for(const auto& line: lines){
        size_t start = 0;
        while(start < line.size()){
            size_t first = line.find_first_not_of(' ', start);
            if(first == std::string::npos) break;
            size_t last = line.find_first_of(' ', first);
            if(last == std::string::npos) last = line.size();
            std::string word = line.substr(first, last-first);
            ++totalWords;
            ++wordCount[word];
            start = last;
        }
    }
}

std::map<std::string, int> WordCounter::getWordCounter(){
    return wordCount;
}

int WordCounter::getTotalWords() const{
    return totalWords;
}

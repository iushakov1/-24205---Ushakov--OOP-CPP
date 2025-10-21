#include "wordcounter.h"

#include <algorithm>
#include <tuple>

void WordCounter::countWords(const std::vector<std::string>& words) {
    for(const auto& word: words){
        ++wordsStat[word];
        ++totalWords;
    }
}

std::vector<std::tuple<std::string, int, double>> WordCounter::getWordCount() {
    std::vector<std::tuple<std::string, int, double>> wordCount;
    for(const auto& wordStat: wordsStat){
        double inProcent = ((double)wordStat.second/totalWords) * 100;
        wordCount.push_back(std::make_tuple(wordStat.first, wordStat.second, inProcent));
    }
    std::sort(wordCount.begin(), wordCount.end(), [](const std::tuple<std::string, int, double>& a, const std::tuple<std::string, int, double>& b){
        return std::get<1>(a) > std::get<1>(b);
    });
    return wordCount;
}







#include "ResultWriter.h"

#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <vector>

ResultWriter::ResultWriter(std::string filename) : filename(std::move(filename)){}

void ResultWriter::write(const std::map<std::string, int>& wordCount, int totalWords){
    std::ofstream outputFile(filename);
    if(totalWords == 0){
        return;
    }
    std::vector<std::pair<std::string, int>> vec(wordCount.begin(), wordCount.end());

    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b)
    {return  a.second > b.second;});
    for (const auto& pair : vec) {
        outputFile << pair.first << ';' << pair.second << ';'
        << ((double)pair.second * 100 / totalWords) << "%" << '\n';
    }
}

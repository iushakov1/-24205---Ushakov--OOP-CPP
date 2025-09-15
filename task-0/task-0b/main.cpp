#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <list>
#include <map>
#include <vector>


int main(int argc, char* argv[]){
    std::string inFileName = argv[1];
    std::ifstream inputFile(inFileName);

    std::string outputFileName = argv[2];
    std::ofstream outputFile(outputFileName);

    std::string line;
    std::list<std::string> lines;
    while(getline(inputFile, line)){
        lines.push_back(line);
    }
    inputFile.close();

    std::map<std::string, int> wordCount;
    int amount = 0;
    for(const auto& listLine: lines){
        size_t start = 0;
        while(start < listLine.size()){
            size_t first = listLine.find_first_not_of(' ', start);
            if(first == std::string::npos) break;

            size_t last = listLine.find_first_of(' ', first);
            if(last == std::string::npos){
                last = listLine.size();
            }
            std::string word = listLine.substr(first, last - first);
            ++amount;
            ++wordCount[word];
            start = last;
        }
    }
    std::cout << std::fixed << std::setprecision(1);

    std::vector<std::pair<std::string, int>> vec(wordCount.begin(), wordCount.end());
    std::sort(
            vec.begin(), vec.end(),
            [](const auto& a, const auto& b){return a.second > b.second;}
            );
    outputFile << std::fixed << std::setprecision(1);
    for(const auto& pair: vec){
         outputFile << pair.first << ' ' << pair.second << ' ' << ((double)pair.second*100/amount) << "%" << '\n';
    }
    outputFile.close();
    return 0;
}

#include "csvwriter.h"
#include "filereader.h"
#include "splitter.h"
#include "wordcounter.h"

#include <vector>

int main(int argc, char* argv[]){
    if(argc != 3){
        return 0;
    }

    FileReader reader(argv[1]);
    Splitter splitter;
    WordCounter counter;
    CSVWriter writer(argv[2]);

    std::vector<std::string> allWords;

    while(reader.hasNext()){
        std::string nextLine = reader.next();
        auto newWords = splitter.split(nextLine);
        allWords.insert(allWords.end(), newWords.begin(), newWords.end());
    }

    counter.countWords(allWords);

    std::vector<std::string> outputData;
    for(const auto& stat: counter.getWordCount()){
        std::string outString = std::get<0>(stat) + ";" + std::to_string(std::get<1>(stat))
                + ";" + std::to_string(std::get<2>(stat)) + '%';
        outputData.push_back(outString);
    }

    writer.write(outputData);

    reader.close();
    writer.close();
}
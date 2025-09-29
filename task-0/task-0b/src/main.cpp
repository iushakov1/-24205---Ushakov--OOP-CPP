#include "csvwriter.h"
#include "filereader.h"
#include "wordcounter.h"

#include <vector>

int main(int argc, char* argv[]){
    if(argc != 3){
        return 0;
    }
    FileReader reader(argv[1]);
    WordCounter counter;
    CSVWriter writer(argv[2]);

    while(true){
        std::vector words = reader.getSplittedLine();
        if(words.empty()){
            break;
        }
        counter.countWords(words);
    }
    writer.writeVector(counter.getWordCount());
    return 0;
}
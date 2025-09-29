#include "filereader.h"

#include <string>
#include <utility>
#include <vector>

FileReader::FileReader(std::string filename):filename(std::move(filename)) {
    input.open(this->filename);
}

std::vector<std::string> FileReader::getSplittedLine() {
    std::vector<std::string> vec;
    std::string line;
    if(!std::getline(input, line)){
        return vec;
    }
    size_t start = 0;
    size_t end = 0;
    while (start != line.size()) {
        start = line.find_first_not_of(" ,.", end);
        if (start == std::string::npos) {
            break;
        }
        end = line.find_first_of(" ,.", start);
        if (end == std::string::npos) {
            end = line.size();
        }
        vec.push_back(line.substr(start, end - start));
    }
    return vec;
}
#include "linesplitter.h"

void Linesplitter::splitLine(const std::string& line) {
    std::vector<std::string> vec;
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
        words.push_back(line.substr(start, end - start));
    }
}

std::vector<std::string> Linesplitter::getWords() {
    return words;
}

void Linesplitter::resetWords() {
    words.clear();
}

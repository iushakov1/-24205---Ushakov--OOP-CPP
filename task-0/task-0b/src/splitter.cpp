#include "splitter.h"

std::vector<std::string> Splitter::split(const std::string& line) {
    std::vector<std::string> vec;
    std::vector<std::string> words;
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
    return words;
}



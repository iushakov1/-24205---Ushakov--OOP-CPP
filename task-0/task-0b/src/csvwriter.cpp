#include "csvwriter.h"

#include <utility>

CSVWriter::CSVWriter(std::string  filename): filename(std::move(filename)) {
    output.open(this->filename);
}

void CSVWriter::writeVector(const std::vector<std::tuple<std::string, int, double>>& vec) {
    for(auto line:vec){
        output << std::get<0>(line) << ' ' << std::get<1>(line) << ' ' << std::get<2>(line) << std::endl;
    }
}


#include "csvwriter.h"

#include <string>
#include <utility>
#include <vector>

CSVWriter::CSVWriter(std::string  filename): filename(std::move(filename)) {
    file.open(this->filename);
}

void CSVWriter::open() {
    file.open(filename);
}

void CSVWriter::close() {
    file.close();
}

void CSVWriter::reset() {
    file.seekp(std::ios::beg);
}

void CSVWriter::write(const std::vector<std::string>& vec) {
    for(const auto& line:vec){
        file << line << std::endl;
    }
}


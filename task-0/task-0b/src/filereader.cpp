#include "filereader.h"

#include <string>
#include <utility>
#include <vector>

FileReader::FileReader(std::string filename):filename(std::move(filename)){
    file.open(this->filename);
}

void FileReader::open() {
    file.open(this->filename);
}

void FileReader::close() {
    file.close();
}

bool FileReader::hasNext() {
    return !file.eof();
}

std::string FileReader::next() {
    std::string nextString;
    getline(file, nextString);
    return nextString;
}

void FileReader::reset() {
    file.seekg(std::ios::beg);
}

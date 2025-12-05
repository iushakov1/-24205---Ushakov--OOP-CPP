#include "filewritter.h"

#include <string>
#include <utility>

FileWriter::FileWriter(std::string filePath): filePath(std::move(filePath)) {
    file.open(this->filePath);
}

void FileWriter::open() {
    file.open(filePath);
}

void FileWriter::close() {
    file.close();
}

void FileWriter::reset() {
    file.seekp(std::ios::beg);
}

void FileWriter::write(const std::string& line) {
    file << line << std::endl;
}
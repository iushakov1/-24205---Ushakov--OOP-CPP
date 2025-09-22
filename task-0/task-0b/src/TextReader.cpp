#ifndef TASK_0B_TEXTREADER_H
#define TASK_0B_TEXTREADER_H

#include "TextReader.h"

#include <list>
#include <string>
#include <fstream>

TextReader::TextReader(std::string  filename) : filename(std::move(filename)){}

std::list<std::string> TextReader::readLines(){
    std::ifstream inputFile(filename);
    std::list<std::string> lines;
    std::string line;

    while(getline(inputFile, line)){
        lines.push_back(line);
    }
    return lines;
}

#endif 
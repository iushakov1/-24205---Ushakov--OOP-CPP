//
// Created by ioanushakov on 04.12.2025.
//

#include "filereader.h"
#include "preset.h"

#include <fstream>
#include <iostream>

Preset::Preset(const std::string &filePath) {
    std::ifstream in(filePath);
    if(!in){
        std::cerr << "cannot open: " << filePath << std::endl;
        exit(1);
    }

    std::string curName;
    std::string curRule;
    getline(in, curName);
    if(!std::getline(in, curName)){
        std::cerr << "wrong file's format: " << filePath << std::endl;
        exit(1);
    }

    if(!std::getline(in, curRule)){
        std::cerr << "wrong file's format: " << filePath << std::endl;
        exit(1);
    }

    path = filePath;
    rule = curRule;
    name = curName.substr(3);
}

void Preset::unload(Universe &u, Rule &r) {
    FileReader reader(path);
    std::string curLine = reader.next();
    if(curLine != "#Life 1.06"){
        std::cout << "incorrect file's format" << std::endl;
        exit(1);
    }
    curLine = reader.next();
    size_t un1 = curLine.find_first_not_of("#N ");
    if (un1 == std::string::npos){
        std::cout << "incorrect universe's name in file" << std::endl;
        exit(1);
    }
    size_t un2 = curLine.find_first_of(' ', un1);
    std::string universeName = (un2 == std::string::npos) ? curLine.substr(un1) : curLine.substr(un1, un2 - un1);

    curLine = reader.next();
    r.loadRule(curLine);
    curLine = reader.next();

    int width, height;
    takeTwoInt(width, height, curLine);

    int fieldSize = width * height;
    std::vector<uint8_t> startField(fieldSize, 0);

    while (reader.hasNext()) {
        curLine = reader.next();
        int x, y;
        takeTwoInt(x, y, curLine);
        if(!(0<=x && x<=width) || !(0<=y && y<=height)){
            std::cout << "incorrect universe cell coordinates in file" << std::endl;
            exit(1);
        }
        startField[(height - 1 - y) * width + x] = 1;
    }
    u.loadUniverse(width, height, universeName, startField);
}

bool Preset::takeTwoInt(int &a, int &b, const std::string& s) {
    size_t i = s.find_first_not_of(' ');
    if (i == std::string::npos) return false;
    size_t j = s.find_first_of(' ', i);
    std::string first = s.substr(i, (j==std::string::npos)? s.size()-i : j-i);

    if (j == std::string::npos) return false;
    size_t k = s.find_first_not_of(' ', j);
    if (k == std::string::npos) return false;
    size_t l = s.find_first_of(' ', k);
    std::string second = s.substr(k, (l==std::string::npos)? s.size()-k : l-k);

    a = std::stoi(first);
    b = std::stoi(second);
    return true;
}

std::string Preset::getRule() const {
    return rule;
}

std::string Preset::getName() const {
    return name;
}

std::string Preset::getPath() const {
    return path;
}
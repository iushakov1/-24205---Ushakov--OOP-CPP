#include "presetio.h"

#include "filereader.h"
#include "filewritter.h"

static bool take2IntFromString(int& a, int& b, const std::string& s) {
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

void PresetIO::load(const std::filesystem::path &filePath, Universe &universe, Rule &rule){
    FileReader reader(filePath);
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
    rule.loadRule(curLine);
    curLine = reader.next();

    int width, height;
    take2IntFromString(width, height, curLine);

    int fieldSize = width * height;
    std::vector<uint8_t> startField(fieldSize, 0);

    while (reader.hasNext()) {
        curLine = reader.next();
        int x, y;
        take2IntFromString(x, y, curLine);
        if(!(0<=x && x<=width) || !(0<=y && y<=height)){
            std::cout << "incorrect universe cell coordinates in file" << std::endl;
            exit(1);
        }
        startField[(height - 1 - y) * width + x] = 1;
    }
    universe.loadUniverse(width, height, universeName, startField);
}

void PresetIO::save(const std::filesystem::path &filePath, const Universe &universe, const Rule &rule){
    FileWriter writer(filePath);
    writer.write("#Life 1.06");
    writer.write("#N " + universe.getName());
    writer.write(rule.getRule());
    writer.write(std::to_string(universe.getWidth()) + " " + std::to_string(universe.getHeight()));
    const uint8_t *data = universe.dataCur();
    for (int y = 0; y < universe.getHeight(); ++y) {
        for (int x = 0; x < universe.getWidth(); ++x) {
            if (*(data + y * universe.getWidth() + x)) {
                writer.write(std::to_string(x) + " " + std::to_string(y));
            }
        }
    }
}
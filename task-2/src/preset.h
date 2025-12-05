//
// Created by ioanushakov on 04.12.2025.
//

#ifndef TASK_2_PRESET_H
#define TASK_2_PRESET_H

#include "rule.h"
#include "universe.h"

#include <filesystem>
#include <string>

class Preset {
public:
    explicit Preset(const std::string& filePath);
    void unload(Universe& universe, Rule& rule);
    std::string getName() const;
    std::string getRule() const;
    std::string getPath() const;
private:
    bool takeTwoInt(int& a, int& b, const std::string& s);
    std::string name;
    std::string rule;
    std::string path;
};


#endif //TASK_2_PRESET_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "presetregistry.h"

PresetRegistry::PresetRegistry(const std::string &path) {
    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
        std::cout << "presets directory is not exists. Aborting run" << std::endl;
        exit(1);
    }
    directoryPath = path;

    PresetInfo curPreset;
    for(const std::filesystem::directory_entry& e : std::filesystem::directory_iterator(path)){
        if(!e.is_regular_file()){
            continue;
        }
        std::ifstream in(e.path());
        if(!in){
            std::cerr << "cannot open: " << e.path().string() << std::endl;
            continue;
        }

        std::string name;
        std::string rule;
        getline(in, name);
        if(!std::getline(in, name)){
            std::cerr << "wrong file's format: " << e.path().string() << std::endl;
            continue;
        }

        if(!std::getline(in, rule)){
            std::cerr << "wrong file's format: " << e.path().string() << std::endl;
            continue;
        }

        curPreset.id = count + 1;
        curPreset.path = e.path();
        curPreset.rule = rule;
        curPreset.name = name.substr(name.find_first_not_of("#N "));;
        presets.push_back(curPreset);
        ++count;
    }
}

int PresetRegistry::loadDirectory(const std::string& path) {

    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
        std::cout << "presets directory is not exists. Aborting run.\n";
        return 1;
    }
    count = 0;
    presets.clear();
    directoryPath = path;

    PresetInfo curPreset;
    for(const std::filesystem::directory_entry& e : std::filesystem::directory_iterator(path)){
        if(!e.is_regular_file()){
            continue;
        }
        std::ifstream in(e.path());
        if(!in){
            std::cerr << "cannot open: " << e.path().string() << std::endl;
            continue;
        }

        std::string name;
        std::string rule;
        getline(in, name);
        if(!std::getline(in, name)){
            std::cerr << "wrong file: " << e.path().string() << std::endl;
            continue;
        }

        if(!std::getline(in, rule)){
            std::cerr << "wrong file: " << e.path().string() << std::endl;
            continue;
        }

        curPreset.id = count + 1;
        curPreset.path = e.path();
        curPreset.rule = rule;
        curPreset.name = name.substr(name.find_first_not_of("#N "));;
        presets.push_back(curPreset);
        ++count;
    }
    return 0;
}

const std::vector<PresetInfo> &PresetRegistry::getPresetList() {
    return presets;
}

int PresetRegistry::getRegistryLen() const {
    return count;
}

std::optional<PresetInfo> PresetRegistry::getPresetByInx(int inx) {
    if(!(0 <= inx-1 && inx-1 <= count-1)){
        std::cout << "wrong index of the parser's list" << std::endl;
        exit(1);
    }
    return presets[inx-1];
}
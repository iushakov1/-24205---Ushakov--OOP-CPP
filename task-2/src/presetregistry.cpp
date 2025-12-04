#include <algorithm>
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

    std::vector<std::filesystem::directory_entry> directoryEntry;
    for(const std::filesystem::directory_entry& e : std::filesystem::directory_iterator(path)){
        if(!e.is_regular_file()){
            continue;
        }
        std::ifstream in(e.path());
        if(!in){
            std::cerr << "cannot open: " << e.path().string() << std::endl;
            continue;
        }
        directoryEntry.push_back(e);
    }
    std::sort(directoryEntry.begin(), directoryEntry.end(), [](const auto& a, const auto& b){ return a.path().filename() < b.path().filename(); });

    for(const auto& e : directoryEntry){
        Preset curPreset(e.path());
        presets.push_back(curPreset);
        ++readCount;
    }
}

const std::vector<Preset> &PresetRegistry::getPresetList() {
    return presets;
}

int PresetRegistry::getRegistryLen() const {
    return readCount;
}

Preset PresetRegistry::getPresetByInx(int inx) {
    if(!(0 <= inx && inx <= readCount-1)){
        std::cout << "wrong index of the parser's list" << std::endl;
        exit(1);
    }
    return presets[inx];
}
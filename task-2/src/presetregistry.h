#ifndef TASK_2_PRESETREGISTRY_H
#define TASK_2_PRESETREGISTRY_H

#include "preset.h"

#include <optional>
#include <string>
#include <vector>

class PresetRegistry {
public:
    explicit PresetRegistry(const std::string& path = "preset");

    const std::vector<Preset>& getPresetList();
    Preset getPresetByInx(int inx);
    int getRegistryLen() const;
private:
    std::string directoryPath;
    std::vector<Preset> presets;
    int readCount = 0;
};

#endif

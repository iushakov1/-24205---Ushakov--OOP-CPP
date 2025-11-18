#ifndef TASK_2_PRESETREGISTRY_H
#define TASK_2_PRESETREGISTRY_H

#include <optional>
#include <string>
#include <vector>

struct PresetInfo{
    int id;
    std::string name;
    std::string rule;
    std::string path;
};
class PresetRegistry {
public:
    PresetRegistry() = default;
    PresetRegistry(const std::string& path);
    int loadDirectory(const std::string& path);
    const std::vector<PresetInfo>& getPresetList();
    std::optional<PresetInfo> getPresetByInx(int inx);
    int getRegistryLen() const;
private:
    std::string directoryPath;
    std::vector<PresetInfo> presets;
    int count = 0;
};

#endif

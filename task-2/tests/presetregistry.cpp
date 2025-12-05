//
// Created by ioanushakov on 05.12.2025.
//

#include "presetregistry.h"
#include "preset.h"

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

static fs::path createPresetDirWithFiles() {
    fs::path baseDir = "preset_registry_tests";
    fs::create_directories(baseDir);

    {
        std::ofstream out(baseDir / "first.life");
        out << "#Life 1.06\n";
        out << "#N FIRST\n";
        out << "#R B3/S23\n";
        out << "3 3\n";
        out << "0 0\n";
    }
    {
        std::ofstream out(baseDir / "second.life");
        out << "#Life 1.06\n";
        out << "#N SECOND\n";
        out << "#R B3/S23\n";
        out << "2 2\n";
        out << "1 1\n";
    }

    return baseDir;
}

TEST(PresetRegistryTest, FindsPresetsInDirectory) {
    fs::path dir = createPresetDirWithFiles();

    PresetRegistry registry(dir.string());
    auto list = registry.getPresetList();

    EXPECT_GE(registry.getRegistryLen(), 2);
    EXPECT_EQ((list.size()), registry.getRegistryLen());

    fs::remove_all(dir);
}

TEST(PresetRegistryTest, GetPresetByIndex) {
    fs::path dir = createPresetDirWithFiles();
    PresetRegistry registry(dir.string());

    ASSERT_GT(registry.getRegistryLen(), 0);
    const auto& list = registry.getPresetList();
    std::vector<std::string> names = {"FIRST", "SECOND"};
    for (int i = 0; i < registry.getRegistryLen(); ++i) {
        const Preset& fromList = list[i];
        const Preset& fromGetter = registry.getPresetByInx(i);

        EXPECT_EQ(fromList.getName(), fromGetter.getName());
        EXPECT_EQ(fromList.getPath(), fromGetter.getPath());
        EXPECT_EQ(fromGetter.getName(), names[i]);
    }

    fs::remove_all(dir);
}

//
// Created by ioanushakov on 05.12.2025.
//
#include "preset.h"
#include "universe.h"
#include "rule.h"

#include <fstream>
#include <string>
#include <gtest/gtest.h>

namespace fs = std::filesystem;

std::string createPreset(const std::string& fileName) {
    std::string presetPath = fileName + ".life";

    std::ofstream out(presetPath);

    out << "#Life 1.06\n";
    out << "#N TEST_PRESET\n";
    out << "#R B3/S23\n";
    out << "3 3\n";
    out << "1 1\n";
    out << "2 2\n";

    return presetPath;
}

TEST(PresetTest, LoadsUniverseAndRuleFromValidFile) {
    auto file = createPreset("preset");

    Preset preset(file);
    Universe u(0, 0, "");
    Rule r;

    preset.unload(u, r);

    EXPECT_EQ(u.getWidth(), 3);
    EXPECT_EQ(u.getHeight(), 3);
    EXPECT_EQ(u.getName(), "TEST_PRESET");

    const uint8_t* data = u.getCurData();
    EXPECT_EQ(data[u.getInxFromCoordinates(1, 1)], 1);
    EXPECT_EQ(data[u.getInxFromCoordinates(2, 2)], 1);

    EXPECT_EQ(r.getRule(), "#R B3/S23");
}
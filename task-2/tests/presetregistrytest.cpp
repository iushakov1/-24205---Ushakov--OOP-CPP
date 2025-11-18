#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include "presetregistry.h"

using std::filesystem::path;

static path makeTempDir(const std::string& prefix) {
    path base = std::filesystem::temp_directory_path() / (prefix + "_XXXXXX");
    std::string s = base.string();
    std::vector<char> tmpl(s.begin(), s.end());
    tmpl.push_back('\0');
    int fd = mkstemp(tmpl.data());
    if (fd != -1) close(fd);
    path p = tmpl.data();
    std::filesystem::remove(p);
    std::filesystem::create_directory(p);
    return p;
}

static void writeFile(const path& p, const std::vector<std::string>& lines) {
    std::ofstream f(p);
    for (auto& ln : lines) f << ln << "\n";
}

#if GTEST_HAS_DEATH_TEST
TEST(PresetRegistryDeathTest, InvalidDirectory_Exits) {
    std::string bad = "/this/dir/does/not/exist";
    EXPECT_EXIT({ PresetRegistry reg(bad); }, ::testing::ExitedWithCode(1), "");
}
#endif

TEST(PresetRegistryTest, LoadDirectoryInvalidDirectoryReturns1) {
    PresetRegistry reg;
    int rc = reg.loadDirectory("/this/dir/does/not/exist");
    EXPECT_EQ(rc, 1);
    EXPECT_EQ(reg.getRegistryLen(), 0);
    EXPECT_TRUE(reg.getPresetList().empty());
}

TEST(PresetRegistryTest, LoadDirectorySkipsNonRegularFiles) {
    auto dir = makeTempDir("presets_nonregular");
    std::filesystem::create_directory(dir / "subdir");
    writeFile(dir / "ok1.life", { "#Life 1.06", "#N Demo 1", "B3/S23" });
    PresetRegistry reg;
    int rc = reg.loadDirectory(dir.string());
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(reg.getRegistryLen(), 1);
    const auto& vec = reg.getPresetList();
    ASSERT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0].id, 1);
    EXPECT_EQ(vec[0].name, "Demo 1");
    EXPECT_EQ(vec[0].rule, "B3/S23");
}

TEST(PresetRegistryTest, LoadDirectory_MultipleFiles) {
    auto dir = makeTempDir("presets_multi");
    writeFile(dir / "a.life", { "#Life 1.06", "#N A", "B3/S23" });
    writeFile(dir / "b.life", { "#Life 1.06", "#N B", "B36/S23" });
    PresetRegistry reg;
    int rc = reg.loadDirectory(dir.string());
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(reg.getRegistryLen(), 2);
    const auto& v = reg.getPresetList();
    ASSERT_EQ(v.size(), 2);
    EXPECT_EQ(v[0].id, 1);
    EXPECT_EQ(v[1].id, 2);
    EXPECT_EQ(v[0].name, "A");
    EXPECT_EQ(v[1].name, "B");
    EXPECT_EQ(v[0].rule, "B3/S23");
    EXPECT_EQ(v[1].rule, "B36/S23");
}

TEST(PresetRegistryTest, LoadDirectory_SkipsBadFiles_FormatsDifferCtorVsLoad) {
    auto dir = makeTempDir("presets_bad");
    writeFile(dir / "bad1.life", { "#Life 1.06" });
    writeFile(dir / "bad2.life", { "#Life 1.06", "#N NameOnly" });
    writeFile(dir / "ok.life", { "#Life 1.06", "#N Name", "B/S" });

    PresetRegistry reg;
    int rc = reg.loadDirectory(dir.string());
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(reg.getRegistryLen(), 1);
    const auto& v = reg.getPresetList();
    ASSERT_EQ(v.size(), 1);
    EXPECT_EQ(v[0].name, "Name");
    EXPECT_EQ(v[0].rule, "B/S");
}

TEST(PresetRegistryTest, GetPresetByInx_ValidIndex) {
    auto dir = makeTempDir("presets_get");
    writeFile(dir / "f.life", { "#Life 1.06", "#N Foo", "B3/S23" });
    writeFile(dir / "g.life", { "#Life 1.06", "#N Bar", "B3678/S23" });

    PresetRegistry reg;
    ASSERT_EQ(reg.loadDirectory(dir.string()), 0);
    auto p1 = reg.getPresetByInx(1);
    auto p2 = reg.getPresetByInx(2);
    ASSERT_TRUE(p1.has_value());
    ASSERT_TRUE(p2.has_value());
    EXPECT_EQ(p1->name, "Foo");
    EXPECT_EQ(p2->name, "Bar");
}

#if GTEST_HAS_DEATH_TEST
TEST(PresetRegistryDeathTest, GetPresetByInx_OutOfRangeExits) {
    auto dir = makeTempDir("presets_idx");
    writeFile(dir / "only.life", { "#Life 1.06", "#N Single", "B3/S23" });
    PresetRegistry reg;
    ASSERT_EQ(reg.loadDirectory(dir.string()), 0);
    EXPECT_EXIT(reg.getPresetByInx(0), ::testing::ExitedWithCode(1), "");
    EXPECT_EXIT(reg.getPresetByInx(-1), ::testing::ExitedWithCode(1), "");
    EXPECT_EXIT(reg.getPresetByInx(2), ::testing::ExitedWithCode(1), "");
}
#endif

TEST(PresetRegistryTest, ConsecutiveLoads_ResetStateAndIds) {
    auto dir1 = makeTempDir("presets_round1");
    auto dir2 = makeTempDir("presets_round2");
    writeFile(dir1 / "a.life", { "#Life 1.06", "#N A1", "B3/S23" });
    writeFile(dir1 / "b.life", { "#Life 1.06", "#N B1", "B36/S23" });
    writeFile(dir2 / "c.life", { "#Life 1.06", "#N C2", "B/S" });

    PresetRegistry reg;
    ASSERT_EQ(reg.loadDirectory(dir1.string()), 0);
    EXPECT_EQ(reg.getRegistryLen(), 2);
    ASSERT_EQ(reg.loadDirectory(dir2.string()), 0);
    EXPECT_EQ(reg.getRegistryLen(), 1);
    const auto& v = reg.getPresetList();
    ASSERT_EQ(v.size(), 1);
    EXPECT_EQ(v[0].id, 1);
    EXPECT_EQ(v[0].name, "C2");
    EXPECT_EQ(v[0].rule, "B/S");
}

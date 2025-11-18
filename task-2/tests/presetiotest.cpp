#include "presetio.h"
#include "rule.h"
#include "universe.h"

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <cstdint>
#include <csignal>

static std::filesystem::path makeTempPath(const std::string& prefix) {
    auto p = std::filesystem::temp_directory_path() / (prefix + "_XXXXXX");
    auto s = p.string();
    std::vector<char> tmpl(s.begin(), s.end());
    tmpl.push_back('\0');
    int fd = mkstemp(tmpl.data());
    if (fd != -1) close(fd);
    return std::filesystem::path(tmpl.data());
}

static std::string readAll(const std::filesystem::path& f) {
    std::ifstream in(f);
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

#if GTEST_HAS_DEATH_TEST
#define MAYBE_DEATH(test_name) test_name
#else
#define MAYBE_DEATH(test_name) DISABLED_##test_name
#endif

TEST(PresetIOTest, SaveWritesExpectedFormat) {
    Universe u;
    Rule r;
    u.loadUniverse(3, 2, "demo", std::vector<uint8_t>{
            1,0,0,
            0,0,1
    });

    auto tmp = makeTempPath("save_ok");
    PresetIO::save(tmp, u, r);

    std::string text = readAll(tmp);

    EXPECT_NE(text.find("#Life 1.06"), std::string::npos);
    EXPECT_NE(text.find("#N demo"), std::string::npos);
    EXPECT_NE(text.find(r.getRule()), std::string::npos);
    EXPECT_NE(text.find("3 2"), std::string::npos);
    EXPECT_NE(text.find("0 0"), std::string::npos);
    EXPECT_NE(text.find("2 1"), std::string::npos);
}

TEST(PresetIOTest, LoadParsesCorrectFile) {
    auto tmp = makeTempPath("load_ok");

    {
        std::ofstream f(tmp);
        f << "#Life 1.06\n";
        f << "#N demo\n";
        f << "#R B5/S23\n";
        f << "3 2\n";
        f << "0 0\n";
        f << "2 1\n";
    }

    Universe u;
    Rule r;
    PresetIO::load(tmp, u, r);

    EXPECT_EQ(u.getName(), "demo");
    EXPECT_EQ(u.getWidth(), 3);
    EXPECT_EQ(u.getHeight(), 2);
    EXPECT_EQ(r.getRule(), "#R B5/S23");

    const uint8_t* cur = u.dataCur();
    std::vector<uint8_t> expect = { 0,0,1, 1,0,0 };
    for (size_t i = 0; i < expect.size(); ++i)
        EXPECT_EQ(cur[i], expect[i]);
}

TEST(PresetIODeathTest, MAYBE_DEATH_Load_BadMagic_Exits) {
    auto tmp = makeTempPath("bad_magic");
    {
        std::ofstream f(tmp);
        f << "#Life 1.05\n";
    }

#if GTEST_HAS_DEATH_TEST
    Universe u; Rule r;
    EXPECT_EXIT(PresetIO::load(tmp, u, r), ::testing::ExitedWithCode(1), "");
#endif
}

TEST(PresetIODeathTest, MAYBE_DEATH_Load_BadUniverseName_Exits) {
    auto tmp = makeTempPath("bad_name");
    {
        std::ofstream f(tmp);
        f << "#Life 1.06\n";
        f << "#N \n";
        f << "B3/S23\n";
        f << "3 2\n";
    }

#if GTEST_HAS_DEATH_TEST
    Universe u; Rule r;
    EXPECT_EXIT(PresetIO::load(tmp, u, r), ::testing::ExitedWithCode(1), "");
#endif
}

TEST(PresetIODeathTest, MAYBE_DEATH_Load_BadCoordinates_Exits) {
    auto tmp = makeTempPath("bad_xy");
    {
        std::ofstream f(tmp);
        f << "#Life 1.06\n";
        f << "#N demo\n";
        f << "#R B3/S23\n";
        f << "3 2\n";
        f << "4 1\n";
    }

#if GTEST_HAS_DEATH_TEST
    Universe u; Rule r;
    EXPECT_EXIT(PresetIO::load(tmp, u, r), ::testing::ExitedWithCode(1), "");
#endif
}

TEST(PresetIOTest, SaveThenLoad_RoundTrip) {
    Universe u0;
    Rule r0;
    u0.loadUniverse(4, 3, "round", std::vector<uint8_t>{
            1,0,0,0,
            0,1,0,0,
            0,0,0,1
    });

    auto tmp = makeTempPath("roundtrip");
    PresetIO::save(tmp, u0, r0);

    Universe u1;
    Rule r1;
    PresetIO::load(tmp, u1, r1);

    EXPECT_EQ(u1.getName(), u0.getName());
    EXPECT_EQ(u1.getWidth(), u0.getWidth());
    EXPECT_EQ(u1.getHeight(), u0.getHeight());
    auto u0cur = u0.dataCur();
    auto u1cur = u1.dataCur();
    auto u0h = u0.getHeight();
    auto u0w = u0.getWidth();
    int i = 0;
    for(int y = 0; y < u0h; ++y){
        for(int x = 0; x < u0w; ++x){
            EXPECT_EQ(u0cur[(u0h-1-y)*u0w + x], u1cur[i]);
            ++i;
        }
    }
}

#include "command.h"
#include "universe.h"
#include "rule.h"

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

static fs::path makeTmp(const std::string& name) {
    fs::path dir = "dumpcommand_tests";
    fs::create_directories(dir);
    return dir / name;
}

TEST(CommandTest, WritesBasicLifeFile) {
    Universe u(2, 2, "TEST");
    Rule r;
    r.loadRule("#R B3/S23");

    uint8_t* data = u.getCurData();
    data[1] = 1;

    fs::path outPath = makeTmp("dump.life");
    std::string outStr = outPath.string();

    DumpCommand cmd(outStr);
    cmd.execute(u, r);

    std::ifstream in(outPath);
    ASSERT_TRUE(in.is_open());

    std::string line;
    std::getline(in, line);
    EXPECT_EQ(line, "#Life 1.06");
    std::getline(in, line);
    EXPECT_NE(line.find("#N TEST"), std::string::npos);
    std::getline(in, line);
    EXPECT_EQ(line, r.getRule());
    std::getline(in, line);
    EXPECT_EQ(line, "2 2");
    std::getline(in, line);
    EXPECT_EQ(line, "1 0");

    fs::remove_all(outPath.parent_path());
}

TEST(CommandTest, TickCommandUsesUniverse) {
    Rule r;
    r.loadRule("#R B3/S23");

    int w = 3, h = 3;
    std::vector<uint8_t> field = {
            0,1,0,
            0,1,0,
            0,1,0
    };
    Universe u(w, h, "test", field);

    TickCommand cmd(1);
    cmd.execute(u, r);

    const uint8_t* data = u.getCurData();
    EXPECT_EQ(data[3+0], 1);
    EXPECT_EQ(data[3+1], 1);
    EXPECT_EQ(data[3+2], 1);
}

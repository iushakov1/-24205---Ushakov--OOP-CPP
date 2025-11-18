#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <vector>

#include "render.h"

struct CoutRedirect {
    std::streambuf* old = nullptr;
    std::ostringstream oss;
    CoutRedirect(){
        old = std::cout.rdbuf(oss.rdbuf());
    }
    ~CoutRedirect() {
        std::cout.rdbuf(old);
    }
    std::string str() const {
        return oss.str();
    }
};

TEST(RenderTest, NoClear_Simple2x2) {
    Render r("X", false);
    uint8_t data[] = {
            1, 0,
            0, 1
    };

    CoutRedirect cap;
    r.draw(data, 2, 2);
    const std::string out = cap.str();

    const std::string expected =
            "X.\n"
            ".X\n";
    EXPECT_EQ(out, expected);
}

TEST(RenderTest, ClearPrinted_FirstThingIsEscape) {
    Render r("A", true);
    uint8_t data[] = {0};
    CoutRedirect cap;
    r.draw(data, 1, 1);
    const std::string out = cap.str();
    const std::string esc = "\x1b[2J\x1b[H";
    ASSERT_GE(out.size(), esc.size());
    EXPECT_EQ(out.substr(0, esc.size()), esc);
}

TEST(RenderTest, DotsForDeadCells) {
    Render r("XYZ", false);
    std::vector<uint8_t> data(6, 0);
    CoutRedirect cap;
    r.draw(data.data(), 3, 2);
    const std::string out = cap.str();
    const std::string expected =
            "...\n"
            "...\n";
    EXPECT_EQ(out, expected);
}

TEST(RenderTest, AlivePatternWrapsBySumXY) {
    Render r("abc", false);
    uint8_t data[] = {
            1,1,1,
            1,1,1
    };
    CoutRedirect cap;
    r.draw(data, 3, 2);
    const std::string out = cap.str();
    const std::string expected =
            "abc\n"
            "bca\n";
    EXPECT_EQ(out, expected);
}

TEST(RenderTest, ZeroWidthOrHeight) {
    Render r("X", false);
    uint8_t dummy{1};
    {
        CoutRedirect cap;
        r.draw(&dummy, 0, 3);
        EXPECT_EQ(cap.str(), "\n\n\n");
    }
    {
        CoutRedirect cap;
        r.draw(&dummy, 3, 0);
        EXPECT_EQ(cap.str(), "");
    }
    {
        Render rc("X", true);
        CoutRedirect cap;
        rc.draw(&dummy, 0, 2);
        EXPECT_EQ(cap.str(), std::string("\x1b[2J\x1b[H\n\n"));
    }
}

TEST(RenderTest, SingleCharAlive) {
    Render r("*", false);
    uint8_t data[] = {1,1,1,1};
    CoutRedirect cap;
    r.draw(data, 2, 2);
    const std::string out = cap.str();
    const std::string expected =
            "**\n"
            "**\n";
    EXPECT_EQ(out, expected);
}
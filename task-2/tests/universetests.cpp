#include <gtest/gtest.h>
#include "universe.h"

using ::testing::ExitedWithCode;

TEST(UniverseTest, Initialization) {
    const int W = 3, H = 2;
    std::vector<uint8_t> start = {1,0,1, 0,1,0};
    Universe u(W, H, "u", start);

    EXPECT_EQ(u.getWidth(), W);
    EXPECT_EQ(u.getHeight(), H);
    EXPECT_EQ(u.getName(), "u");

    const uint8_t* cur = u.getCurData();
    const uint8_t* nxt = u.getNextData();
    for (int i = 0; i < W*H; ++i) {
        EXPECT_EQ(cur[i], start[i]);
        EXPECT_EQ(nxt[i], 0);
    }
}

TEST(UniverseTest, ZeroInitialization) {
    const int W = 4, H = 3;
    Universe u(W, H, "empty");
    EXPECT_EQ(u.getWidth(), W);
    EXPECT_EQ(u.getHeight(), H);
    EXPECT_EQ(u.getName(), "empty");

    const uint8_t* cur = u.getCurData();
    const uint8_t* nxt = u.getNextData();
    for (int i = 0; i < W*H; ++i) {
        EXPECT_EQ(cur[i], 0);
        EXPECT_EQ(nxt[i], 0);
    }
}

TEST(UniverseDeathTest, ValueCtorWithWrongStartFieldSize_Dies) {
    std::vector<uint8_t> bad = {1,0,1};
    EXPECT_EXIT({ Universe u(2, 2, "bad", bad); }, ExitedWithCode(1), "invalid sizes for start field");
}

TEST(UniverseTest, ReinitializesUniverse) {
    Universe u(2, 2, "a", std::vector<uint8_t>{1,0,0,1});

    auto* nxt0 = u.getNextData();
    nxt0[0] = 7; nxt0[1] = 7; nxt0[2] = 7; nxt0[3] = 7;

    u.loadUniverse(3, 1, "b", std::vector<uint8_t>{9,8,7});
    EXPECT_EQ(u.getWidth(), 3);
    EXPECT_EQ(u.getHeight(), 1);
    EXPECT_EQ(u.getName(), "b");

    const uint8_t* cur = u.getCurData();
    const uint8_t* nxt = u.getNextData();
    EXPECT_EQ(cur[0], 9);
    EXPECT_EQ(cur[1], 8);
    EXPECT_EQ(cur[2], 7);
    EXPECT_EQ(nxt[0], 0);
    EXPECT_EQ(nxt[1], 0);
    EXPECT_EQ(nxt[2], 0);
}

TEST(UniverseDeathTest, LoadUniverseWithWrongStartFieldSize) {
    Universe u(1, 1, "x");
    EXPECT_EXIT({ u.loadUniverse(3, 1, "y", std::vector<uint8_t>{1,2}); },
                ExitedWithCode(1), "invalid sizes for start field");
}

TEST(UniverseTest, SwapBuffers) {
    Universe u(2, 2, "u", std::vector<uint8_t>{1,2,3,4});
    auto* nxt = u.getNextData();
    nxt[0]=9; nxt[1]=8; nxt[2]=7; nxt[3]=6;

    EXPECT_EQ(u.getCurData()[0], 1);
    EXPECT_EQ(u.getCurData()[1], 2);
    EXPECT_EQ(u.getCurData()[2], 3);
    EXPECT_EQ(u.getCurData()[3], 4);

    EXPECT_EQ(u.getNextData()[0], 9);
    EXPECT_EQ(u.getNextData()[1], 8);
    EXPECT_EQ(u.getNextData()[2], 7);
    EXPECT_EQ(u.getNextData()[3], 6);

    u.swapBuffers();

    EXPECT_EQ(u.getCurData()[0], 9);
    EXPECT_EQ(u.getCurData()[1], 8);
    EXPECT_EQ(u.getCurData()[2], 7);
    EXPECT_EQ(u.getCurData()[3], 6);

    EXPECT_EQ(u.getNextData()[0], 1);
    EXPECT_EQ(u.getNextData()[1], 2);
    EXPECT_EQ(u.getNextData()[2], 3);
    EXPECT_EQ(u.getNextData()[3], 4);
}

TEST(UniverseTest, DataCurPointers) {
    Universe u(2, 2, "u");
    uint8_t* cur = u.getCurData();
    uint8_t* nxt = u.getNextData();
    cur[0]=5; cur[1]=6; cur[2]=7; cur[3]=8;
    nxt[0]=1; nxt[1]=2; nxt[2]=3; nxt[3]=4;

    EXPECT_EQ(u.getCurData()[0], 5);
    EXPECT_EQ(u.getCurData()[1], 6);
    EXPECT_EQ(u.getCurData()[2], 7);
    EXPECT_EQ(u.getCurData()[3], 8);
    EXPECT_EQ(u.getNextData()[0], 1);
    EXPECT_EQ(u.getNextData()[1], 2);
    EXPECT_EQ(u.getNextData()[2], 3);
    EXPECT_EQ(u.getNextData()[3], 4);
}

TEST(UniverseTest, SetNameChangesName) {
    Universe u(1, 1, "old");
    EXPECT_EQ(u.getName(), "old");
    u.setName("new");
    EXPECT_EQ(u.getName(), "new");
}
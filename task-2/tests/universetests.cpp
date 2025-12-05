//
// Created by ioanushakov on 05.12.2025.
//

#include <gtest/gtest.h>
#include "universe.h"
#include "rule.h"

TEST(UniverseTest, ConstructEmptyUniverse) {
    Universe u(5, 4, "test");
    EXPECT_EQ(u.getWidth(), 5);
    EXPECT_EQ(u.getHeight(), 4);
    EXPECT_EQ(u.getName(), "test");
}

TEST(UniverseTest, LoadUniverseFromVector) {
    int w = 3, h = 3;
    std::vector<uint8_t> field = {
        0,1,0,
        0,1,0,
        0,1,0
    };
    Universe u(w, h, "line", field);
    EXPECT_EQ(u.getWidth(), w);
    EXPECT_EQ(u.getHeight(), h);
    const uint8_t* data = u.getCurData();
    EXPECT_EQ(data[1], 1);
    EXPECT_EQ(data[4], 1);
    EXPECT_EQ(data[7], 1);
}

TEST(UniverseTest, Evolve) {
    Rule r;
    r.loadRule("#R B3/S23");

    int w = 3, h = 3;
    std::vector<uint8_t> field = {
        0,1,0,
        0,1,0,
        0,1,0
    };
    Universe u(w, h, "evolve", field);

    u.evolve(r);
    const uint8_t* data = u.getCurData();
    EXPECT_EQ(data[3+0], 1);
    EXPECT_EQ(data[3+1], 1);
    EXPECT_EQ(data[3+2], 1);
}
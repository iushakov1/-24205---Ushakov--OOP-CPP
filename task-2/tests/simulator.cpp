#include <gtest/gtest.h>
#include <vector>

#include "simulator.h"
#include "rule.h"
#include "universe.h"

TEST(SimulatorTest, AccessorsReflectUniverseAndRule) {
    Universe u(3, 2, "demo");
    Rule r("B3/S23");
    Simulator sim(u, r);

    EXPECT_EQ(sim.getUniverseWidth(), 3);
    EXPECT_EQ(sim.getUniverseHeight(), 2);
    EXPECT_EQ(sim.getUniverseName(), "demo");
    EXPECT_EQ(sim.getRule(), "#R B3/S23");

    EXPECT_EQ(sim.getUniverseData(), u.dataCur());
}

TEST(SimulatorTest, TickZeroDoesNothing) {
    Universe u(2, 1, "u", {1,0});
    Rule r("B1/S1");
    Simulator sim(u, r);

    const uint8_t* before = sim.getUniverseData();
    sim.tick(0);
    const uint8_t* after = sim.getUniverseData();

    EXPECT_EQ(before, after);
}

TEST(SimulatorTest, TickOneSwapsBuffers) {
    Universe u(2, 1, "u", {1,0});
    Rule r("#R B1/S1");

    Simulator sim(u, r);
    const uint8_t* before = sim.getUniverseData();
    sim.tick(1);
    const uint8_t* after = sim.getUniverseData();

    EXPECT_NE(before, after);
}

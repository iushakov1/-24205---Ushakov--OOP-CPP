#include <gtest/gtest.h>
#include "universe.h"
#include "rule.h"
#include "stepper.h"

static void stepAndSwap(Universe& u, const Rule& r) {
    Stepper s(u);
    s.nextStep(r);
    u.swapBuffers();
}

TEST(StepperUniverseIntegration, EmptyWorldStaysEmpty) {
    Universe u(3, 3, "u", std::vector<uint8_t>(9, 0));
    Rule r("B3/S23");
    stepAndSwap(u, r);
    for (int i = 0; i < 9; ++i){
        EXPECT_EQ(u.dataCur()[i], 0);
    }
}

TEST(StepperUniverseIntegration, SingleCellDies) {
    std::vector<uint8_t> start = {
            0,0,0,
            0,1,0,
            0,0,0
    };
    Universe u(3, 3, "u", start);
    Rule r("B3/S23");
    stepAndSwap(u, r);
    for (int i = 0; i < 9; ++i) EXPECT_EQ(u.dataCur()[i], 0);
}

TEST(StepperUniverseIntegration, ToroidalEdges) {
    std::vector<uint8_t> start = {
            1,0,1,
            0,1,0,
            1,0,0
    };
    Universe u(3, 3, "u", start);
    Rule r("B3/S23");

    stepAndSwap(u, r);
    EXPECT_EQ(u.dataCur()[0], 1);
}

TEST(StepperUniverseIntegration, DimensionsAndAccessors) {
    Universe u(4, 3, "name");
    EXPECT_EQ(u.getWidth(), 4);
    EXPECT_EQ(u.getHeight(), 3);
    EXPECT_EQ(u.getName(), "name");
    ASSERT_NE(u.dataCur(), nullptr);
    ASSERT_NE(u.dataNext(), nullptr);
}

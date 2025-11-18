#ifndef TASK_2_SIMULATOR_H
#define TASK_2_SIMULATOR_H

#include "rule.h"
#include "stepper.h"
#include "universe.h"

class Simulator {
public:
    Simulator(Universe& universe, Rule& rule);
    void tick(int t);
    [[nodiscard]] const uint8_t* getUniverseData() const noexcept;
    [[nodiscard]] int getUniverseWidth() const noexcept;
    [[nodiscard]] int getUniverseHeight() const noexcept;
    [[nodiscard]] std::string getUniverseName() const noexcept;
    [[nodiscard]] std::string getRule() const noexcept;
private:

    Universe& universe;
    Rule& rule;
    int generation;

};

#endif
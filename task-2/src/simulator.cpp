#include "simulator.h"
#include "render.h"

Simulator::Simulator(Universe &universe, Rule &rule): universe(universe), rule(rule){
    generation = 0;
}

const uint8_t *Simulator::getUniverseData() const noexcept {
    return universe.dataCur();
}

int Simulator::getUniverseHeight() const noexcept {
    return universe.getHeight();
}

int Simulator::getUniverseWidth() const noexcept {
    return universe.getWidth();
}

std::string Simulator::getUniverseName() const noexcept {
    return universe.getName();
}

std::string Simulator::getRule() const noexcept {
    return rule.getRule();
}

void Simulator::tick(int t) {
    Stepper stepper(universe);
    for (int i = 0; i < t; ++i) {
        stepper.nextStep(rule);
        universe.swapBuffers();
        ++generation;
    }
}
#ifndef TASK_2_STEPPER_H
#define TASK_2_STEPPER_H

#include "universe.h"
#include "rule.h"

class Stepper {
public:
    explicit Stepper(Universe& universe);
    void nextStep(const Rule& rule);
private:
    int getInxFromCoord(int x, int y);
    int getNumOfNeighbours(int index);
    Universe& universe;
};

#endif

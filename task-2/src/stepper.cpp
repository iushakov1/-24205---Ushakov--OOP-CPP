#include "stepper.h"

Stepper::Stepper(Universe &universe): universe(universe) {}

void Stepper::nextStep(const Rule& rule) {
    const auto cur = universe.dataCur();
    auto next = universe.dataNext();
    for(int i = 0; i < universe.getWidth()*universe.getHeight(); ++i){
        int numOfNeighbours = getNumOfNeighbours(i);
        *(next+i) = rule.decide(numOfNeighbours, *(cur+i));
    }
}

int Stepper::getInxFromCoord(int x, int y){
    return y * universe.getWidth() + x;
}

int Stepper::getNumOfNeighbours(int i) {
    const int w = universe.getWidth();
    const int h = universe.getHeight();
    const uint8_t* cur = universe.dataCur();

    const int x = i % w;
    const int y = i / w;

    const int xm = (x + w - 1) % w;
    const int xp = (x + 1) % w;
    const int ym = (y + h - 1) % h;
    const int yp = (y + 1) % h;

    int s = 0;
    s += cur[getInxFromCoord(xm, ym)];
    s += cur[getInxFromCoord(x , ym)];
    s += cur[getInxFromCoord(xp, ym)];
    s += cur[getInxFromCoord(xm, y )];
    s += cur[getInxFromCoord(xp, y )];
    s += cur[getInxFromCoord(xm, yp)];
    s += cur[getInxFromCoord(x , yp)];
    s += cur[getInxFromCoord(xp, yp)];
    return s;
}
#include "universe.h"

#include <iostream>
#include <utility>

Universe::Universe(int xSize, int ySize, std::string name ,std::vector<uint8_t> startField): xSize(xSize), ySize(ySize), name(std::move(name)){
    if((size_t)xSize*(size_t)ySize != startField.size()){
        std::cerr << "invalid sizes for start field" << std::endl;
        exit(1);
    }
    curField = std::move(startField);
    nextField.assign(xSize*ySize, 0);
}

Universe::Universe(int xSize, int ySize, std::string name):xSize(xSize), ySize(ySize), name(std::move(name)){
    size_t n = (size_t)xSize*(size_t)ySize;
    curField.assign(n, 0);
    nextField.assign(n, 0);
}

void Universe::loadUniverse(int lxSize, int lySize, std::string lname, std::vector<uint8_t> startField) {
    xSize = lxSize;
    ySize = lySize;
    name = std::move(lname);
    if((size_t)xSize*(size_t)ySize != startField.size()){
        std::cerr << "invalid sizes for start field" << std::endl;
        exit(1);
    }
    curField = std::move(startField);
    nextField.assign(xSize*ySize, 0);
}

void Universe::setName(std::string newName) {
    this->name = std::move(newName);
}

void Universe::evolve(const Rule &rule) {
    auto curData = curField.data();
    auto nextData = nextField.data();
    for(int i = 0; i < xSize*ySize; ++i){
        int numOfNeighbours = getNumOfNeighbours(i);
        *(nextData+i) = rule.decide(numOfNeighbours, *(curData+i));
    }
    swapBuffers();
}

int Universe::getHeight() const noexcept {
    return ySize;
}

int Universe::getWidth() const noexcept {
    return xSize;
}

const uint8_t* Universe::getCurData() const noexcept {
    return curField.data();
}
uint8_t* Universe::getCurData() noexcept{
    return curField.data();
}
const uint8_t* Universe::getNextData() const noexcept{
    return nextField.data();
}
uint8_t* Universe::getNextData() noexcept {
    return nextField.data();
}

void Universe::swapBuffers() noexcept {
    curField.swap(nextField);
}

std::string Universe::getName() const noexcept {
    return name;
}

int Universe::getInxFromCoordinates(int x, int y) {
    return y * xSize + x;
}

int Universe::getNumOfNeighbours(int index) {
    const int w = xSize;
    const int h = ySize;

    const int x = index % w;
    const int y = index / w;

    const int xm = (x + w - 1) % w;
    const int xp = (x + 1) % w;
    const int ym = (y + h - 1) % h;
    const int yp = (y + 1) % h;

    int s = 0;
    s += curField[getInxFromCoordinates(xm, ym)];
    s += curField[getInxFromCoordinates(x , ym)];
    s += curField[getInxFromCoordinates(xp, ym)];
    s += curField[getInxFromCoordinates(xm, y )];
    s += curField[getInxFromCoordinates(xp, y )];
    s += curField[getInxFromCoordinates(xm, yp)];
    s += curField[getInxFromCoordinates(x , yp)];
    s += curField[getInxFromCoordinates(xp, yp)];
    return s;
}
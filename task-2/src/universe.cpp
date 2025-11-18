#include "universe.h"

#include <iostream>
#include <utility>

Universe::Universe(int xSize, int ySize, std::string name ,std::vector<uint8_t> startField): xSize(xSize), ySize(ySize), name(std::move(name)){
    if((size_t)xSize*(size_t)ySize != startField.size()){
        std::cerr << "invalid sizes for start field" << std::endl;
        exit(1);
    }
    prevField = std::move(startField);
    nextField.assign(xSize*ySize, 0);
}

Universe::Universe(int xSize, int ySize, std::string name):xSize(xSize), ySize(ySize), name(std::move(name)){
    size_t n = (size_t)xSize*(size_t)ySize;
    prevField.assign(n, 0);
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
    prevField = std::move(startField);
    nextField.assign(xSize*ySize, 0);
}

void Universe::setName(std::string newName) {
    this->name = std::move(newName);
}

int Universe::getHeight() const noexcept {
    return ySize;
}

int Universe::getWidth() const noexcept {
    return xSize;
}

const uint8_t* Universe::dataCur() const noexcept {
    return prevField.data();
}
uint8_t* Universe::dataCur() noexcept{
    return prevField.data();
}
const uint8_t* Universe::dataNext() const noexcept{
    return nextField.data();
}
uint8_t* Universe::dataNext() noexcept {
    return nextField.data();
}

void Universe::swapBuffers() noexcept {
    prevField.swap(nextField);
}

std::string Universe::getName() const noexcept {
    return name;
}
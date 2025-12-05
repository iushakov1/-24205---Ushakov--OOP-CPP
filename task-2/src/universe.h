#ifndef TASK_2_UNIVERSE_H
#define TASK_2_UNIVERSE_H

#include "rule.h"

#include <cstdint>
#include <string>
#include <vector>

class Universe {
public:
    Universe() = default;
    Universe(int xSize, int ySize, std::string name, std::vector<uint8_t> startField);
    Universe(int xSize, int ySize, std::string name);

    void loadUniverse(int xSize, int ySize, std::string name, std::vector<uint8_t> startField);
    void setName(std::string name);
    void evolve(const Rule& rule);

    const uint8_t* getCurData() const noexcept;
    uint8_t*       getCurData() noexcept;
    const uint8_t* getNextData() const noexcept;
    uint8_t*       getNextData() noexcept;
    int getWidth() const noexcept;
    int getHeight() const noexcept;
    std::string getName() const noexcept;
    int getInxFromCoordinates(int x, int y) const;
private:
    int getNumOfNeighbours(int index);
    void swapBuffers() noexcept;
    std::vector<uint8_t> curField;
    std::vector<uint8_t> nextField;
    int xSize{};
    int ySize{};
    std::string name;
};

#endif

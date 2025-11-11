#ifndef TASK_2_UNIVERSE_H
#define TASK_2_UNIVERSE_H

#include <cstdint>
#include <string>
#include <vector>

class Universe {
public:
    Universe() = default;
    Universe(int xSize, int ySize, std::string name, std::vector<uint8_t> startField);
    Universe(int xSize, int ySize, std::string name);
    void loadUniverse(int xSize, int ySize, std::string name, std::vector<uint8_t> startField);
    void swapBuffers() noexcept;
    void setName(std::string name);
    [[nodiscard]] int getWidth() const noexcept;
    [[nodiscard]] int getHeight() const noexcept;
    [[nodiscard]] const uint8_t* dataCur() const noexcept;
    uint8_t*       dataCur() noexcept;
    [[nodiscard]] const uint8_t* dataNext() const noexcept;
    uint8_t*       dataNext() noexcept;
    [[nodiscard]] std::string getName() const noexcept;
private:
    std::vector<uint8_t> prevField;
    std::vector<uint8_t> nextField;
    int xSize{};
    int ySize{};
    std::string name;
};

#endif

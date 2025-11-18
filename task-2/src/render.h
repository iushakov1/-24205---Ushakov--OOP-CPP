#ifndef TASK_2_RENDER_H
#define TASK_2_RENDER_H

#include <cstdint>
#include <string>

class Render {
public:
    explicit Render(std::string aliveInons = "0", bool clear=true);
    void draw(const uint8_t* data, int w, int h) noexcept;
private:
    std::string alive;
    bool isClear;
};


#endif

#ifndef TASK_2_RENDER_H
#define TASK_2_RENDER_H

#include <cstdint>
#include <string>

class Render {
public:
    explicit Render(bool isClear=false);
    void draw(const uint8_t* data, int w, int h) noexcept;
private:
    bool isClear;
};


#endif

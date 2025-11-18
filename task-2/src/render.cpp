#include "render.h"

#include <iostream>
#include <utility>

Render::Render(std::string alive, bool clear) : alive(std::move(alive)), isClear(clear) {}

void Render::draw(const uint8_t *data, int w, int h) noexcept {
    if(isClear){
        std::cout << "\x1b[2J\x1b[H";
    }
    for(int y = 0; y < h; ++y){
        std::string line;
        line.resize(size_t(w));
        const uint8_t* row = data + size_t(y)*w;
        for(int x = 0; x < w; ++x){
            line[x] = row[x] ? alive[(x+y)%(alive.size())] : '.';
        }
        std::cout << line << '\n';
    }
}
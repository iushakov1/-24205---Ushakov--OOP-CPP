#ifndef TASK_2_PRESETIO_H
#define TASK_2_PRESETIO_H

#include <filesystem>
#include <iostream>
#include <expected>

#include "rule.h"
#include "universe.h"

class PresetIO {
public:
    static void load(const std::filesystem::path& file, Universe& u, Rule& r);
    static void save(const std::filesystem::path& file, const Universe& u, const Rule& r);
private:
};


#endif

//
// Created by ioanushakov on 05.12.2025.
//

#ifndef TASK_2_MODEPARSER_H
#define TASK_2_MODEPARSER_H


#include "mode.h"
#include "universe.h"

class ModeParser {
public:
    ModeParser(Universe& universe, Rule& rule);
    Mode* parseMode(int argc, char** argv);
private:
    Universe& universe;
    Rule& rule;
};

#endif //TASK_2_MODEPARSER_H

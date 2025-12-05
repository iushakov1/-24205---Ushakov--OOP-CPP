//
// Created by ioanushakov on 05.12.2025.
//

#ifndef TASK_2_COMMANDPARSER_H
#define TASK_2_COMMANDPARSER_H

#include "universe.h"
#include "command.h"

class CommandParser {
public:
    CommandParser(Universe& universe, Rule& rule);
    Command* parseCommand(std::string& string);
private:
    bool getNWordFromString(int N, const std::string& s, std::string& out);
    Universe& universe;
    Rule& rule;
};


#endif //TASK_2_COMMANDPARSER_H

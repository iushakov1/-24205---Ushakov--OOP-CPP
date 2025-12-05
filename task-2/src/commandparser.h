//
// Created by ioanushakov on 05.12.2025.
//

#ifndef TASK_2_COMMANDPARSER_H
#define TASK_2_COMMANDPARSER_H

#include "universe.h"
#include "command.h"

class CommandParser {
public:
    CommandParser() = default;
    Command* parseCommand(std::string& string);
private:
    bool getWordFromString(int pos, const std::string& s, std::string& out);
};


#endif //TASK_2_COMMANDPARSER_H

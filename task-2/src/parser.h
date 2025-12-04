#ifndef TASK_2_PARSER_H
#define TASK_2_PARSER_H

#include "command.h"
#include "mode.h"

#include <string>
#include <variant>

class Parser {
public:
    Parser(Universe& universe, Rule& rule);
    Command* parseCommand(std::string& string);
    Mode* parseArg(int argc, char** argv);
private:
    bool getNWordFromString(int N, const std::string& s, std::string& out);
    Universe& universe;
    Rule& rule;
};


#endif
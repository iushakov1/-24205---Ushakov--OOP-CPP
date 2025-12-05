//
// Created by ioanushakov on 05.12.2025.
//

#include "commandparser.h"

CommandParser::CommandParser(Universe &universe, Rule &rule) : universe(universe), rule(rule){}

Command* CommandParser::parseCommand(std::string& string) {
    std::string fWord;
    getNWordFromString(1, string, fWord);
    if(fWord == "exit"){
        return new ExitCommand();
    }
    else if(fWord == "dump"){
        std::string sWord;
        if(!getNWordFromString(2, string, sWord)){
            return new ErrorCommand("dump without file's path");
        }
        return new DumpCommand(universe, rule, sWord);
    }
    else if(fWord == "t" || fWord == "tick"){
        std::string sWord;
        if(!getNWordFromString(2, string, sWord)){
            return new TickCommand(universe, rule, 1);
        }
        return new TickCommand(universe, rule, std::stoi(sWord));
    }
    else if(fWord == "help"){
        return new HelpCommand();
    }
    else{
        return new ErrorCommand("unknown command");
    }
}

bool CommandParser::getNWordFromString(int N, const std::string &s, std::string &out) {
    int n = 1;
    size_t i1 = 0;
    size_t i2 = 0;
    while(n <= N) {
        i1 = s.find_first_not_of(' ', i2);
        if (i1 == std::string::npos) return false;
        i2 = s.find_first_of(' ', i1);
        if(i2 == std::string::npos){
            i2 = s.size();
        }
        if(n == N) {
            out = s.substr(i1, (i2 == std::string::npos) ? s.size() - i1 : i2 - i1);
            return true;
        }
        ++n;
    }
    return false;
}
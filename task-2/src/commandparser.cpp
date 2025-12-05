//
// Created by ioanushakov on 05.12.2025.
//

#include "commandparser.h"

Command* CommandParser::parseCommand(std::string& string) {
    std::string fWord;
    getWordFromString(1, string, fWord);
    if(fWord == "exit"){
        return new ExitCommand();
    }
    else if(fWord == "dump"){
        std::string sWord;
        if(!getWordFromString(2, string, sWord)){
            return new ErrorCommand("dump without file's path");
        }
        return new DumpCommand(sWord);
    }
    else if(fWord == "t" || fWord == "tick"){
        std::string sWord;
        if(!getWordFromString(2, string, sWord)){
            return new TickCommand(1);
        }
        return new TickCommand(std::stoi(sWord));
    }
    else if(fWord == "help"){
        return new HelpCommand();
    }
    else{
        return new ErrorCommand("unknown command");
    }
}

bool CommandParser::getWordFromString(int pos, const std::string &s, std::string &out) {
    if(s.empty()){
        return false;
    }
    int n = 1;
    size_t i1 = 0;
    size_t i2 = 0;
    while(n <= pos) {
        i1 = s.find_first_not_of(' ', i2);
        if (i1 == std::string::npos) return false;
        i2 = s.find_first_of(' ', i1);
        if(i2 == std::string::npos){
            i2 = s.size();
        }
        if(n == pos) {
            out = s.substr(i1, (i2 == std::string::npos) ? s.size() - i1 : i2 - i1);
            return true;
        }
        ++n;
    }
    return false;
}
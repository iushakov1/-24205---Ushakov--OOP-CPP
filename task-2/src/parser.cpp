#include <filesystem>
#include <fstream>
#include <iostream>

#include "parser.h"

Parser::Parser(Universe &universe, Rule &rule) : universe(universe), rule(rule) {}

Command* Parser::parseCommand(std::string& string) {
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

Mode* Parser::parseArg (int argc, char **argv) {

    std::fstream tryToOpen;
    if(argc == 4) {
        std::string inputPath;
        int iter;
        std::string outputPath;
        tryToOpen.open(argv[1]);
        if (tryToOpen.is_open()) {
            inputPath = argv[1];
        } else {
            return new ErrorMode("first argument is not a correct input file path");
        }
        tryToOpen.close();

        std::string possibleNum = argv[2];
        if(possibleNum.find_first_not_of("0123456789") != std::string::npos){
            return new ErrorMode("second argument is not a correct iterations number");
        }
        iter = std::stoi(argv[2]);

        outputPath = argv[3];
        tryToOpen.open(outputPath);
        if (!tryToOpen.is_open()) {
            return new ErrorMode("third argument is not a correct output path");
        }
        tryToOpen.close();

        return new OfflineMode(universe, rule, inputPath, iter, outputPath);
    }
    else if(argc == 2){
        tryToOpen.open(argv[1]);
        if (!tryToOpen.is_open()) {
            return new ErrorMode("invalid file's path");
        }
        std::string inputPath = argv[1];
        return new FileMode(universe, rule, inputPath);
    }
    else if(argc == 1){
        std::cout << "enter preset's directory or use enter to search in standard directory" << std::endl;
        std::string dir;
        std::getline(std::cin, dir);
        return new PresetMode(universe, rule, dir.empty() ? "presets" : dir );
    }
    return new ErrorMode("unexpected mode.\nto unload from presets directory throw no arguments\n"
                         "to unload from specific file write it's path\n"
                         "to use offline mode write 3 arguments: input file path, iterations number and output path");
}

bool Parser::getNWordFromString(int N, const std::string &s, std::string &out) {
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
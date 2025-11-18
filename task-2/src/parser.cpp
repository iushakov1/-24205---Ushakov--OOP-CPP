#include <filesystem>
#include <fstream>

#include "parser.h"

std::variant<Command, ParseError> Parser::parseCommand(std::string& string) {
    Command command;
    std::string fWord;
    getNWordFromString(1, string, fWord);
    if(fWord == "exit"){
        command.name = fWord;
        return command;
    }
    else if(fWord == "dump"){
        command.name = fWord;
        std::string sWord;
        if(!getNWordFromString(2, string, sWord)){
            ParseError error;
            error.message = "dump without file's path\n";
            return error;
        }
        command.args = sWord;
        return command;
    }
    else if(fWord == "t" || fWord == "tick"){
        command.name = "tick";
        std::string sWord;
        if(!getNWordFromString(2, string, sWord)){
            command.digitParam = 1;
            return command;
        }
        command.digitParam = std::stoi(sWord);
        return command;
    }
    else if(fWord == "help"){
        command.name = "help";
        return command;
    }
    else{
        ParseError error;
        error.message = "unknown command";
        return error;
    }
}

std::variant<Options, ParseError> Parser::parseArgv(int argc, char **argv) {
    Options options;
    ParseError error;
    std::fstream tryToOpen;
    if(argc == 4) {
        options.mode = 3;
        std::string inputPath;
        int iter;
        std::string outputPath;
        tryToOpen.open(argv[1]);

        if (tryToOpen.is_open()) {
            inputPath = argv[1];
        } else {
            error.message = "first argument is not a correct input file path";
            return error;
        }
        tryToOpen.close();

        std::string possibleNum = argv[2];
        if(possibleNum.find_first_not_of("0123456789") != std::string::npos){
            error.message = "second argument is not a correct iterations number";
            return error;
        }
        iter = std::stoi(argv[2]);

        outputPath = argv[3];
        tryToOpen.open(outputPath);
        if (!tryToOpen.is_open()) {
            error.message = "third argument is not a correct output path";
            return error;
        }
        tryToOpen.close();

        options.inputPath = inputPath;
        options.outputPath = outputPath;
        options.iteration = iter;
        return options;
    }
    if(argc == 2){
        tryToOpen.open(argv[1]);
        if (!tryToOpen.is_open()) {
            error.message = "invalid file's path";
            return error;
        }
        options.mode = 2;
        std::string inputPath = argv[1];
        options.inputPath = inputPath;
        return options;
    }
    else if(argc == 1){
        options.mode = 1;
        return options;
    }
    error.message = "unexpected mode.\nto load from presets directory throw no arguments\n"
                    "to load from specific file write it's path\n"
                    "to use offline mode write 3 arguments: input file path, iterations number and output path";
    return error;
}
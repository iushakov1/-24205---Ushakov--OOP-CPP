#include <cstring>
#include <filesystem>

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
        error.message = "no such command\n";
        return error;
    }
}

std::variant<Options, ParseError> Parser::parseArgv(int argc, char **argv) {
    Options options;
    ParseError error;

    if(argc >= 4) {
        options.mode = 3;
        std::string inputPath;
        int iter;
        std::string outputPath;

        if (std::strncmp(argv[1], "--input=", 8) == 0) {
            inputPath = argv[1] + 8;
        } else if (std::filesystem::is_directory(argv[1])) {
            inputPath = argv[1];
        } else {
            error.message = "input directory is invalid\n";
            return error;
        }

        int argIndex = 0;

        if (std::strncmp(argv[2], "--iterations=", 13) == 0) {
            iter = std::stoi(argv[2] + 13);
            argIndex = 3;
        }
        else if (std::strcmp(argv[2], "-i") == 0) {
            iter = std::stoi(argv[3]);
            if(argc < 5){
                error.message = "not enough arguments";
                return error;
            }
            argIndex = 4;
        } else {
            error.message = "input iterations parameter is invalid\n";
            return error;
        }


        if (std::strncmp(argv[argIndex], "--output=", 9) == 0) {
            outputPath = argv[argIndex] + 9;
        }
        else if (std::strcmp(argv[argIndex], "-o") == 0) {
            outputPath = argv[argIndex + 1];
            if(argc < 5 + (argIndex == 4)){
                error.message = "not enough arguments";
                return error;
            }
        } else {
            error.message = "input output's path is invalid\n";
            return error;
        }
        options.inputPath = inputPath;
        options.outputPath = outputPath;
        options.iteration = iter;
        return options;
    }
    if(argc == 2){
        options.mode = 2;
        std::string inputPath = argv[1];
        options.inputPath = inputPath;
        return options;
    }
    else if(argc == 1){
        options.mode = 1;
        return options;
    }
    error.message = "unexpected mode";
    return error;
}
//
// Created by ioanushakov on 05.12.2025.
//


#include "modeparser.h"
#include "mode.h"
#include "universe.h"
#include "rule.h"

#include <fstream>
#include <iostream>
#include <string>

ModeParser::ModeParser(Universe &universe, Rule &rule) : universe(universe), rule(rule){}

Mode* ModeParser::parseMode(int argc, char **argv) {
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

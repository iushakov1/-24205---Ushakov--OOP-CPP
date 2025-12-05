//
// Created by ioanushakov on 05.12.2025.
//

#include "modeparser.h"
#include "mode.h"

#include <fstream>
#include <string>

Mode* ModeParser::parseMode(int argc, char **argv) {
    std::fstream tryToOpen;
    switch (argc) {
        case 4:{
            std::string inputPath;
            int iter;
            std::string outputPath;
            tryToOpen.open(argv[1]);
            if (tryToOpen.is_open()) {
                inputPath = argv[1];
            } else {
                return new ErrorMode("mode parser: first argument is not a correct input file path");
            }
            tryToOpen.close();

            std::string possibleNum = argv[2];
            if(possibleNum.find_first_not_of("0123456789") != std::string::npos){
                return new ErrorMode("mode parser: second argument is not a correct iterations number");
            }
            iter = std::stoi(argv[2]);

            outputPath = argv[3];

            return new OfflineMode(inputPath, iter, outputPath);
        }
        case 2:{
            tryToOpen.open(argv[1]);
            if (!tryToOpen.is_open()) {
                return new ErrorMode("mode parser: invalid file's path");
            }
            std::string inputPath = argv[1];
            return new FileMode(inputPath);
        }
        case 1:{
            return new PresetMode();
        }
        default:{
            return new ErrorMode("mode parser: unexpected mode.\nto load from presets directory throw no arguments\n"
                                 "to load from specific file write it's path\n"
                                 "to use offline mode write 3 arguments: input file path, iterations number and output path");
        }
    }
}

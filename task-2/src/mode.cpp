//
// Created by ioanushakov on 04.12.2025.
//

#include "preset.h"
#include "mode.h"
#include "presetregistry.h"
#include "render.h"
#include "command.h"
#include "parser.h"

#include <iostream>
#include <utility>

PresetMode::PresetMode(Universe& universe, Rule& rule, std::string dirPath) : universe(universe), rule(rule), presetDir(std::move(dirPath)){}

void PresetMode::start() {
    description();
    PresetRegistry registry(presetDir);

    auto regList = registry.getPresetList();
    for(int i = 0; i < registry.getRegistryLen(); ++i){
        std::cout << i << ": " << regList[i].getName() << std::endl;
    }
    std::cout << "choose a presets by it's index or quit the program pressing exit" << std::endl;
    std::string userInput;
    int userChoice;
    while(true){
        std::getline(std::cin, userInput);
        if(userInput == "exit"){
            exit(0);
        }
        if(userInput.find_first_not_of("0123456789") != std::string::npos){
            std::cout << "incorrect. Try again" << std::endl;
            continue;
        }
        userChoice = std::stoi(userInput);
        if(!(0<=userChoice && userChoice < registry.getRegistryLen())){
            std::cout << "incorrect. Try again" << std::endl;
            continue;
        }
        break;
    }

    auto preset = registry.getPresetByInx(userChoice);
    FileMode filemode(universe, rule, preset.getPath());
    filemode.start();
}

void PresetMode::description() {
    std::cout << "Here you can use command \"tick(or just t) <n>,\" to show the game on the n stage. If you miss the n param it'll be 1.\n"
                 "Also, you can use command \"dump <path.filename>\" to save your current stage of Life.\n"
                 "to see command's list again write \"help\" or you can write \"exit\" to end the work of programm.\n" << std::endl;
}

FileMode::FileMode(Universe& universe, Rule& rule, std::string filePath) : universe(universe), rule(rule), filePath(std::move(filePath)){}
void FileMode::start() {
    description();
    Preset preset(filePath);
    preset.unload(universe, rule);

    Render render(false);
    render.draw(universe.getCurData(), universe.getWidth(), universe.getHeight());

    Parser parser(universe, rule);
    std::string userInput;
    while(true){
        std::getline(std::cin, userInput);
        auto command = parser.parseCommand(userInput);
        command->execute();
        render.draw(universe.getCurData(), universe.getWidth(), universe.getHeight());
    }
}

void FileMode::description() {
    std::cout << "Here you can choose one of the game's presets\n"
                 "storaging in \"presets\" directory\n"
                 "or quit the program by writing \"exit\"\n\n";
}

OfflineMode::OfflineMode(Universe& universe, Rule& rule, std::string inputPath, int ticks, std::string outputPath): universe(universe), rule(rule), inputPath(std::move(inputPath)),
ticks(ticks), outputPath(std::move(outputPath)) {}
void OfflineMode::start() {
    Preset preset(inputPath);
    preset.unload(universe, rule);

    for(int i = 0; i < ticks; ++i){
        universe.evolve(rule);
    }
    DumpCommand command(universe, rule, outputPath);
    command.execute();
}

ErrorMode::ErrorMode(const std::string& message) {
    std::cerr << message << std::endl;
}
void ErrorMode::start() {
    std::cerr << "cannot launch an error mode" << std::endl;
}

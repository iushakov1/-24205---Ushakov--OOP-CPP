#include <iostream>

#include "parser.h"
#include "presetio.h"
#include "presetregistry.h"
#include "render.h"
#include "rule.h"
#include "simulator.h"
#include "universe.h"

class App{
public:
    App(int argc, char** argv) : argc(argc), argv(argv){}
    void run(){
        auto parsed = Parser::parseArgv(argc, argv);
        Options options;
        if(!std::get_if<Options>(&parsed)){
            auto error = std::get<ParseError>(parsed);
            auto message = error.message;
            throw std::invalid_argument(message);
        }
        options = std::get<Options>(parsed);
        switch (options.mode) {
            case 1: {
                mode1();
                break;
            }
            case 2: {
                mode2(options.inputPath);
                break;
            }
            case 3: {
                mode3(options.inputPath, options.iteration, options.outputPath);
                std::cout << "successful" << std::endl;
                break;
            }
        }
    }
private:

    static void mode1(){
        description(1);
        PresetRegistry registry;
        registry.loadDirectory("presets");
        for(auto& p: registry.getPresetList()){
            std::cout << p.id << " " << p.name << std::endl;
        }
        std::cout << "choose a presets by it's index or quit the program pressing 0" << std::endl;
        int userChoice = -1;
        while(userChoice!=0 && !(std::cin >> userChoice)){
            std::cout << "incorrect index. Try again" << std::endl;
        }
        if(userChoice == 0){
            return;
        }
        std::cin.ignore();
        auto presetInfo = registry.getPresetByInx(userChoice);

        Universe universe;
        Rule rule;
        PresetIO::load(presetInfo->path, universe, rule);
        startGame(universe, rule);
    }

    static void mode2(std::string& filePath){
        Universe universe;
        Rule rule;
        PresetIO::load(filePath, universe, rule);
        description(2);
        startGame(universe, rule);
    }

    static void mode3(const std::string& inputPath, int iteration, const std::string& outputPath){
        Universe universe;
        Rule rule;
        PresetIO::load(inputPath, universe, rule);
        Simulator simulator(universe, rule);
        simulator.tick(iteration);
        PresetIO::save(outputPath, universe, rule);
    }

    static void startGame(Universe& universe, Rule& rule){
        Simulator simulator(universe, rule);
        Render render("@%*0", true);
        render.draw(universe.dataCur(), universe.getWidth(), universe.getHeight());
        help();
        Command command = getUserCommand();
        while(command.name != "exit"){
            if(command.name == "dump"){
                PresetIO::save(command.args, universe, rule);
            }
            else if(command.name == "tick"){
                simulator.tick(command.digitParam);
                render.draw(universe.dataCur(), universe.getWidth(), universe.getHeight());
            }
            else if(command.name == "help"){
                help();
            }
            command = getUserCommand();
        }
    }

    static Command getUserCommand(){
        std::string userInput;
        std::getline(std::cin, userInput);
        auto parsed = Parser::parseCommand(userInput);
        if(!std::get_if<Command>(&parsed)){
            auto error = std::get<ParseError>(parsed);
            throw std::invalid_argument(error.message);
        }
        return std::get<Command>(parsed);
    }

    static void description(int mode){
        switch (mode) {
            case 1:
                std::cout << "Here you can use command \"tick(or just t) <n>,\" to show the game on the n stage. If you miss the n param it'll be 1.\n"
                             "Also, you can use command \"dump <path.filename>\" to save your current stage of Life.\n"
                             "to see command's list again write \"help\" or you can write \"exit\" to end the work of programm." << std::endl;
                break;
            case 2:
                std::cout << "Here you can choose one of the game's presets\n"
                             "storaging in \"presets\" directory\n"
                             "or quit the program by writing \"exit\"\n";
            default:
                break;
        }
    }

    static void help(){
        std::cout << "dump <filename>: saves current life file\n"
                     << "tick <n>: scroll to n life's stage and show it\n" <<
                     "exit: end the program" << std::endl;
    }

    int argc;
    char** argv;
};

int main(int argc, char** argv) {
    App app(argc, argv);
    app.run();
}

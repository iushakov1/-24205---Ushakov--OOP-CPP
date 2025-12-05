//
// Created by ioanushakov on 04.12.2025.
//

#include <iostream>

#include "command.h"
#include "filewritter.h"
#include "render.h"

DumpCommand::DumpCommand(std::string &dumpPath) : dumpPath(dumpPath) {}

void DumpCommand::execute(Universe &universe, Rule &rule) {
    FileWriter writer(dumpPath);
    writer.write("#Life 1.06");
    writer.write("#N " + universe.getName());
    writer.write(rule.getRule());
    writer.write(std::to_string(universe.getWidth()) + " " + std::to_string(universe.getHeight()));
    const uint8_t *data = universe.getCurData();
    for (int y = 0; y < universe.getHeight(); ++y) {
        for (int x = 0; x < universe.getWidth(); ++x) {
            if (*(data + y * universe.getWidth() + x)) {
                writer.write(std::to_string(x) + " " + std::to_string(y));
            }
        }
    }
}

TickCommand::TickCommand(int numOfTicks): numOfTicks(numOfTicks) {}

void TickCommand::execute(Universe &universe, Rule &rule) {
    for(int i = 0; i < numOfTicks; ++i){
        universe.evolve(rule);
    }
    Render render(false);
    render.draw(universe.getCurData(), universe.getWidth(), universe.getHeight());
}

int TickCommand::getNumOfTicks() {
    return numOfTicks;
}

void HelpCommand::execute(Universe &universe, Rule &rule) {
    std::cout << "dump <filename>: saves current life file\n"
              << "tick <n>: scroll to n life's stage and show it\n" <<
              "exit: end the program" << std::endl;
}

void ExitCommand::execute(Universe &universe, Rule &rule) {
    exit(0);
}

ErrorCommand::ErrorCommand(const std::string& errorMessage) {
    std::cerr << errorMessage << std::endl;
}

void ErrorCommand::execute(Universe &universe, Rule &rule) {
    std::cout << "cannot execute an unknown command.\nUse help to see the command list." << std::endl;
}
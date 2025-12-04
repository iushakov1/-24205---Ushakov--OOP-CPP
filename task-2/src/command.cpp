//
// Created by ioanushakov on 04.12.2025.
//

#include <iostream>

#include "command.h"
#include "filewritter.h"
#include "mode.h"

DumpCommand::DumpCommand(Universe &universe, Rule &rule, std::string &dumpPath) : universe(universe), rule(rule), dumpPath(dumpPath) {}

void DumpCommand::execute() {
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

TickCommand::TickCommand(Universe &universe, Rule &rule, int numOfTicks):universe(universe), rule(rule), numOfTicks(numOfTicks) {}

void TickCommand::execute() {
    for(int i = 0; i < numOfTicks; ++i){
        universe.evolve(rule);
    }
}

void HelpCommand::execute() {
    std::cout << "dump <filename>: saves current life file\n"
              << "tick <n>: scroll to n life's stage and show it\n" <<
              "exit: end the program" << std::endl;
}

void ExitCommand::execute() {
    exit(0);
}

ErrorCommand::ErrorCommand(const std::string& errorMessage) {
    std::cerr << errorMessage << std::endl;
}

void ErrorCommand::execute() {
    std::cerr << "cannot execute a wrong command" << std::endl;
}
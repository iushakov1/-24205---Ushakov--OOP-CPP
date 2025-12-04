//
// Created by ioanushakov on 04.12.2025.
//

#ifndef TASK_2_COMMAND_H
#define TASK_2_COMMAND_H

#include "rule.h"
#include "universe.h"

#include <string>

class Command {
public:
    virtual void execute() = 0;
};

class DumpCommand : public Command{
public:
    DumpCommand(Universe& universe, Rule& rule, std::string& dumpPath);
    void execute() override;
private:
    Universe& universe;
    Rule& rule;
    std::string dumpPath;
};

class TickCommand : public Command{
public:
    TickCommand(Universe& universe, Rule& rule, int numOfTicks);
    void execute() override;
private:
    Universe& universe;
    Rule& rule;
    int numOfTicks;
};

class HelpCommand : public Command{
public:
    HelpCommand() = default;
    void execute() override;
private:
};

class ExitCommand : public Command{
public:
    ExitCommand() = default;
    void execute() override;
private:
};

class ErrorCommand : public Command{
public:
    ErrorCommand(const std::string& errorMessage);
    void execute() override;
private:
};

#endif //TASK_2_COMMAND_H

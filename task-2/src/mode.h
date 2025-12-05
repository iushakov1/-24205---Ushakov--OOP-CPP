//
// Created by ioanushakov on 04.12.2025.
//

#ifndef TASK_2_MODE_H
#define TASK_2_MODE_H

#include <string>
#include "command.h"

class Mode {
public:
    virtual void start() = 0;
    virtual void description() = 0;
};

class PresetMode: public Mode{
public:
    PresetMode() =default;
    void start() override;
    void description() override;
private:
};

class FileMode: public Mode{
public:
    FileMode(std::string filePath);
    void start() override;
    void description() override;
private:
    std::string filePath;
};

class OfflineMode: public Mode{
public:
    OfflineMode(std::string inputPath, int ticks, std::string outputPath);
    void start() override;
    void description() override{};
private:
    std::string inputPath;
    std::string outputPath;
    int ticks;
};

class ErrorMode: public Mode{
public:
    ErrorMode(const std::string& message);
    void start() override;
    void description() override{};
private:
};


#endif //TASK_2_MODE_H

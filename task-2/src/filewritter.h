#ifndef TASK_2_FILEWRITTER_H
#define TASK_2_FILEWRITTER_H

#include <fstream>
#include <string>

class FileWriter {
public:
    explicit FileWriter(std::string filePath);
    void open();
    void close();
    void reset();
    void write(const std::string&);
private:
    std::string filePath;
    std::ofstream file;
};

#endif

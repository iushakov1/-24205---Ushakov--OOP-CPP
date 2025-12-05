#ifndef TASK_2_FILEREADER_H
#define TASK_2_FILEREADER_H

#include <fstream>
#include <string>
#include <vector>

class FileReader {
public:
    explicit FileReader(std::string filename);
    void open();
    void close();
    bool hasNext();
    std::string next();
    void reset();
private:
    std::string filename;
    std::ifstream file;
};
#endif
